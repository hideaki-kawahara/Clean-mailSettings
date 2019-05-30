# -*- coding: utf-8 -*-

##
## change ReVIEW source code
##

module ReVIEW

  ## ブロック命令
  Compiler.defblock :program, 0..3      ## プログラム
  Compiler.defblock :terminal, 0..3     ## ターミナル

  ## インライン命令
  Compiler.definline :secref            ## 節(Section)や項(Subsection)を参照


  Book::ListIndex.class_eval do

    ## '//program' と '//terminal' をサポートするよう拡張
    def self.item_type  # override
      #'(list|listnum)'            # original
      '(list|listnum|program|terminal)'
    end

    ## '//list' や '//terminal' のラベル（第1引数）を省略できるよう拡張
    def self.parse(src, *args)  # override
      items = []
      seq = 1
      src.grep(%r{\A//#{item_type}}) do |line|
        if id = line.slice(/\[(.*?)\]/, 1)
          next if id.empty?                     # 追加
          items.push item_class.new(id, seq)
          seq += 1
          ReVIEW.logger.warn "warning: no ID of #{item_type} in #{line}" if id.empty?
        end
      end
      new(items, *args)
    end

  end


  Book::Compilable.module_eval do

    def content   # override
      ## //list[?] や //terminal[?] の '?' をランダム文字列に置き換える。
      ## こうすると、重複しないラベルをいちいち指定しなくても、ソースコードや
      ## ターミナルにリスト番号がつく。ただし @<list>{} での参照はできない。
      unless @_done
        pat = Book::ListIndex.item_type  # == '(list|listnum|program|terminal)'
        @content = @content.gsub(/^\/\/#{pat}\[\?\]/) { "//#{$1}[#{_random_label()}]" }
        @_done = true
      end
      @content
    end

    module_function

    def _random_label
      "_" + rand().to_s[2..10]
    end

  end


  Catalog.class_eval do

    def parts_with_chaps
      ## catalog.ymlの「CHAPS:」がnullのときエラーになるのを防ぐ
      (@yaml['CHAPS'] || []).flatten.compact
    end

  end


  class Builder

    protected

    def truncate_if_endwith?(str)
      sio = @output   # StringIO object
      if sio.string.end_with?(str)
        pos = sio.pos - str.length
        sio.seek(pos)
        sio.truncate(pos)
        true
      else
        false
      end
    end

    def enter_context(key)
      @doc_status[key] = true
    end

    def exit_context(key)
      @doc_status[key] = nil
    end

    def with_context(key)
      enter_context(key)
      return yield
    ensure
      exit_context(key)
    end

    def within_context?(key)
      return @doc_status[key]
    end

    def within_codeblock?
      d = @doc_status
      d[:program] || d[:terminal] \
      || d[:list] || d[:emlist] || d[:listnum] || d[:emlistnum] \
      || d[:cmd] || d[:source]
    end

  end


  class LATEXBuilder

    CODEBLOCK_OPTIONS = {
      'fold'   => true,
      'lineno' => false,
      'linenowidth' => -1,
      'eolmark'     => false,
      'foldmark'    => true,
      'lang'        => nil,
    }

    ## プログラム用ブロック命令
    ## ・//list と似ているが、長い行を自動的に折り返す
    ## ・seqsplit.styの「\seqsplit{...}」コマンドを使っている
    def program(lines, id=nil, caption=nil, optionstr=nil)
      _codeblock('program', lines, id, caption, optionstr)
    end

    ## ターミナル用ブロック命令
    ## ・//cmd と似ているが、長い行を自動的に折り返す
    ## ・seqsplit.styの「\seqsplit{...}」コマンドを使っている
    def terminal(lines, id=nil, caption=nil, optionstr=nil)
      _codeblock('terminal', lines, id, caption, optionstr)
    end

    def _codeblock(blockname, lines, id, caption, optionstr)
      opts = _parse_codeblock_optionstr(optionstr, blockname)
      CODEBLOCK_OPTIONS.each {|k, v| opts[k] = v unless opts.key?(k) }
      #
      if opts['eolmark']
        lines = lines.map {|line| "#{detab(line)}\\startereolmark{}" }
      else
        lines = lines.map {|line| detab(line) }
      end
      #
      if id.present? || caption.present?
        str = _build_caption_str(id, caption)
        puts "\\starterlistcaption{#{str}}"
        puts "\\label{#{id}}" if id
      end
      #
      if within_context?(:note)
        yes = truncate_if_endwith?("\\begin{starternoteinner}\n")
        puts "\\end{starternoteinner}" unless yes
      end
      #
      environ = "starter#{blockname}"
      print "\\begin{#{environ}}"
      print "\\startersetfoldmark{}" unless opts['foldmark']
      if opts['eolmark']
        print "\\startereolmarkdark{}"  if blockname == 'terminal'
        print "\\startereolmarklight{}" if blockname != 'terminal'
      end
      if opts['lineno']
        n = opts['lineno']
        n = 1 if n == true
        width = opts['linenowidth']
        if width && width >= 0
          width = (lines.length + n - 1).to_s.length if width == 0
          print "\\startersetfoldindentwidth{#{'9'*(width+2)}}"
          format = "\\textcolor{gray}{%#{width}d:} "
        else
          format = "\\starterlineno{%s}"
        end
        buf = []
        opt_fold = opts['fold']
        lines.each do |x|
          buf << ( opt_fold \
                   ? "#{format % n}\\seqsplit{#{x}}" \
                   : "#{format % n}#{x}" )
          n += 1
        end
        print buf.join("\n")
      else
        print "\\seqsplit{"       if opts['fold']
        print lines.join("\n")
        print "}"                 if opts['fold']
      end
      puts "\\end{#{environ}}"
      puts "\\begin{starternoteinner}" if within_context?(:note)
      nil
    end

    private

    def _parse_codeblock_optionstr(optionstr, blockname)  # parse 'fold={on|off}'
      opts = {}
      return opts if optionstr.nil? || optionstr.empty?
      vals = {nil=>true, 'on'=>true, 'off'=>false}
      optionstr.split(',').each_with_index do |x, i|
        x = x.strip()
        x =~ /\A([-\w]+)(?:=(.*))?\z/  or
          raise "//#{blockname}[][][#{x}]: invalid option format."
        k, v = $1, $2
        case k
        when 'fold', 'eolmark', 'foldmark'
          if vals.key?(v)
            opts[k] = vals[v]
          else
            raise "//#{blockname}[][][#{x}]: expected 'on' or 'off'."
          end
        when 'lineno'
          if vals.key?(v)
            opts[k] = vals[v]
          elsif v =~ /\A\d+\z/
            opts[k] = v.to_i
          else
            raise "//#{blockname}[][][#{x}]: expected 'on/off' or start number."
          end
        when 'linenowidth'
          if v =~ /\A-?\d+\z/
            opts[k] = v.to_i
          else
            raise "//#{blockname}[][][#{x}]: expected integer value."
          end
        when 'lang'
          if v
            opts[k] = v
          else
            raise "//#{blockname}[][][#{x}]: requires option value."
          end
        else
          if i == 0
            opts['lang'] = v
          else
            raise "//#{blockname}[][][#{x}]: unknown option."
          end
        end
      end
      return opts
    end

    def _build_caption_str(id, caption)
      str = ""
      with_context(:caption) do
        str = compile_inline(caption) if caption.present?
      end
      if id.present?
        number = _build_caption_number(id)
        prefix = "#{I18n.t('list')}#{number}#{I18n.t('caption_prefix')}"
        str = "#{prefix}#{str}"
      end
      return str
    end

    def _build_caption_number(id)
      chapter = get_chap()
      number = @chapter.list(id).number
      return chapter.nil? \
           ? I18n.t('format_number_header_without_chapter', [number]) \
           : I18n.t('format_number_header', [chapter, number])
    rescue KeyError
      error "no such list: #{id}"
    end

    public

    ## ・\caption{} のかわりに \reviewimagecaption{} を使うよう修正
    ## ・「scale=X」に加えて「pos=X」も受け付けるように拡張
    def image_image(id, caption, metric)
      pos, metric = _detect_image_pos(metric)  # detect 'pos=H' or 'pos=h'
      pos.nil? || pos =~ /\A[Hhtb]+\z/  or  # H: Here, h: here, t: top, b: bottom
        raise "//image[][][pos=#{pos}]: expected 'pos=H' or 'pos=h'."
      metrics = parse_metric('latex', metric)
      puts "\\begin{reviewimage}[#{pos}]%%#{id}" if pos
      puts "\\begin{reviewimage}%%#{id}"         unless pos
      metrics = "width=\\maxwidth" unless metrics.present?
      puts "\\includegraphics[#{metrics}]{#{@chapter.image(id).path}}"
      with_context(:caption) do
        #puts macro('caption', compile_inline(caption)) if caption.present?  # original
        puts macro('reviewimagecaption', compile_inline(caption)) if caption.present?
      end
      puts macro('label', image_label(id))
      puts "\\end{reviewimage}"
    end

    private

    def _detect_image_pos(metric)  # detect 'pos=H' or 'pos=h' in metric string
      pos = nil; xs = []
      metric.split(',').each do |x|
        x = x.strip
        x =~ /\Apos=(\S*?)\z/ ? (pos = $1) : (xs << x)
      end if metric
      metric = xs.join(",") if pos
      return pos, metric
    end

    public

    ## 節 (Section) や項 (Subsection) を参照する。
    ## 引数 id が節や項のラベルでないなら、エラー。
    ## 使い方： @<subsec>{label}
    def inline_secref(id)  # 参考：ReVIEW::Builder#inline_hd(id)
      sec_id = id
      chapter = nil
      if id =~ /\A([^|]+)\|(.+)/
        chap_id = $1; sec_id = $2
        chapter = @book.contents.detect {|chap| chap.id == chap_id }  or
          error "@<secref>{#{id}}: chapter '#{chap_id}' not found."
      end
      begin
        _inline_secref(chapter || @chapter, sec_id)
      rescue KeyError
        error "@<secref>{#{id}}: section (or subsection) not found."
      end
    end

    private

    def _inline_secref(chap, id)
      sec_id = chap.headline(id).id
      num, title = _get_secinfo(chap, sec_id)
      label = "sec:" + num.gsub('.', '-')
      level = num.split('.').length
      #
      secnolevel = @book.config['secnolevel']
      if secnolevel + 1 < level
        error "'secnolevel: #{secnolevel}' should be >= #{level-1} in config.yml"
      ## config.ymlの「secnolevel:」が3以上なら、項 (Subsection) にも
      ## 番号がつく。なので、節 (Section) のタイトルは必要ない。
      elsif secnolevel + 1 > level
        parent_title = nil
      ## そうではない場合は、節 (Section) と項 (Subsection) とを組み合わせる。
      ## たとえば、"「1.1 イントロダクション」内の「はじめに」" のように。
      elsif secnolevel + 1 == level
        parent_id = sec_id.sub(/\|[^|]+\z/, '')
        _, parent_title = _get_secinfo(chap, parent_id)
      else
        raise "not reachable"
      end
      #
      return _build_secref(level, label, title, parent_title)
    end

    def _get_secinfo(chap, id)  # 参考：ReVIEW::LATEXBuilder#inline_hd_chap()
      n = chap.headline_index.number(id)
      if chap.number && @book.config['secnolevel'] >= n.split('.').size
        str = I18n.t('chapter_quote', "#{chap.headline_index.number(id)} #{compile_inline(chap.headline(id).caption)}")
      else
        str = I18n.t('chapter_quote', compile_inline(chap.headline(id).caption))
      end
      num, title = n, str
      return num, title
    end

    def _build_secref(level, label, title, parent_title)
      s = ""
      ## 親セクションのタイトルがあれば使う
      if parent_title
        s << "%s内の" % parent_title   # TODO: I18n化
      end
      ## 対象セクションへのリンクを作成する
      if @book.config['chapterlink']
        s << "\\reviewsecref{#{title}}{#{label}}"
      else
        s << title
      end
      return s
    end

  end


  class PDFMaker

    ### original: 2.4, 2.5
    #def call_hook(hookname)
    #  return if !@config['pdfmaker'].is_a?(Hash) || @config['pdfmaker'][hookname].nil?
    #  hook = File.absolute_path(@config['pdfmaker'][hookname], @basehookdir)
    #  if ENV['REVIEW_SAFE_MODE'].to_i & 1 > 0
    #    warn 'hook configuration is prohibited in safe mode. ignored.'
    #  else
    #    system_or_raise("#{hook} #{Dir.pwd} #{@basehookdir}")
    #  end
    #end
    ### /original

    def call_hook(hookname)
      if ENV['REVIEW_SAFE_MODE'].to_i & 1 > 0
        warn 'hook configuration is prohibited in safe mode. ignored.'
        return
      end
      d = @config['pdfmaker']
      return if d.nil? || !d.is_a?(Hash) || d[hookname].nil?
      ## hookname が文字列の配列なら、それらを全部実行する
      [d[hookname]].flatten.each do |hook|
        script = File.absolute_path(hook, @basehookdir)
        ## 拡張子が .rb なら、rubyコマンドで実行する（ファイルに実行属性がなくてもよい）
        if script.end_with?('.rb')
          ruby = ruby_fullpath()
          ruby = "ruby" unless File.exist?(ruby)
          system_or_raise("#{ruby} #{script} #{Dir.pwd} #{@basehookdir}")
        else
          system_or_raise("#{script} #{Dir.pwd} #{@basehookdir}")
        end
      end
    end

    private
    def ruby_fullpath
      require 'rbconfig'
      c = RbConfig::CONFIG
      return File.join(c['bindir'], c['ruby_install_name']) + c['EXEEXT'].to_s
    end

  end

end
