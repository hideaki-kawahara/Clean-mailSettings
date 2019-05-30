= Re:VIEW Starter FAQ

//abstract{
残念ながら、Re:VIEWでできないことは、Starterでもたいていできません。

このFAQでは、「何ができないか？」を中心に解説します。
//}

#@#//makechaptitlepage[toc=section]

== コメント

=== 範囲コメントはないの？

ありません。必要な範囲に行コメント「@<code>$#@#$」をつけてください。頑張れ。


=== 行コメントを使ったら勝手に段落が分かれたんだけど、なんで？

Re:VIEWの仕様です。

たとえば次のような5行は、1つの段落になります。

//emlist[サンプル]{
これから王国の復活を祝って、諸君にラピュタの力を見せてやろうと思ってね。
見せてあげよう、ラピュタの雷を！
旧約聖書にある、ソドムとゴモラを滅ぼした天の火だよ。
ラーマーヤナではインドラの矢とも伝えているがね。
全世界は再びラピュタのもとにひれ伏すことになるだろう。
//}

//noindent
@<em>{表示結果：}@<br>{}

これから王国の復活を祝って、諸君にラピュタの力を見せてやろうと思ってね。
見せてあげよう、ラピュタの雷を！
旧約聖書にある、ソドムとゴモラを滅ぼした天の火だよ。
ラーマーヤナではインドラの矢とも伝えているがね。
全世界は再びラピュタのもとにひれ伏すことになるだろう。

//blankline



ここで途中の行（3行目）をコメントアウトすると、段落が2つに分かれてしまいます。

//emlist[サンプル]{
これから王国の復活を祝って、諸君にラピュタの力を見せてやろうと思ってね。
見せてあげよう、ラピュタの雷を！
@<code>$#@$#旧約聖書にある、ソドムとゴモラを滅ぼした天の火だよ。
ラーマーヤナではインドラの矢とも伝えているがね。
全世界は再びラピュタのもとにひれ伏すことになるだろう。
//}

//noindent
@<em>{表示結果：}@<br>{}

これから王国の復活を祝って、諸君にラピュタの力を見せてやろうと思ってね。
見せてあげよう、ラピュタの雷を！
#@#旧約聖書にある、ソドムとゴモラを滅ぼした天の火だよ。
ラーマーヤナではインドラの矢とも伝えているがね。
全世界は再びラピュタのもとにひれ伏すことになるだろう。

//blankline



なぜかというと、コメントアウトされた箇所が空行として扱われるからです、まるでこのように：

//emlist[サンプル]{
これから王国の復活を祝って、諸君にラピュタの力を見せてやろうと思ってね。
見せてあげよう、ラピュタの雷を！

ラーマーヤナではインドラの矢とも伝えているがね。
全世界は再びラピュタのもとにひれ伏すことになるだろう。
//}



段落が分かれてしまうのはこのような理由ですが、これはRe:VIEWの仕様バグというべきですね。


== 箇条書き

=== 順序つき箇条書きに「A.」や「a.」や「i.」を使いたい

できません。
Re:VIEWでは、順序つき箇条書きとしては「1. 」や「2. 」という書き方しかサポートしていません。
数字ではなくアルファベットを使おうと「A. 」や「a. 」のようにしても、できません。
Re:VIEWの文法を拡張するしかないです。


=== 順序つき箇条書きを入れ子にできない？

できません。
Re:VIEWでは、順序なし箇条書きは入れ子にできますが、順序つき箇条書きは入れ子にできません。
#@#また順序つき箇条書きの中に順序なし箇条書きを入れ子にすることもできません。
箇条書きの入れ子をインデントで表現するような文法だとよかったのですが、残念ながらRe:VIEWはそのような仕様になっていません。

とりあえずの回避策としては、順序つき箇条書きの中で「1.」や「(A)」を使ってください。

//emlist[サンプル]{
 * (A) 大項目
 ** (1) 中項目
 *** (1-a) 小項目
 *** (1-b) 小項目
 ** (2) 中項目
//}

//noindent
@<em>{表示結果：}@<br>{}

 * (A) 大項目
 ** (1) 中項目
 *** (1-a) 小項目
 *** (1-b) 小項目
 ** (2) 中項目

//blankline




=={sec-faq-block} ブロック命令

==={subsec-faq-block1} ブロックの中に別のブロックを入れるとエラーになるよ？

Re:VIEWの仕様です。

Re:VIEWでは、たとえば「@<code>$//note{$ ... @<code>$//}$」の中に「@<code>$//emlist{$ ... @<code>$//}$」を入れると、エラーになります。
これはかなり困った仕様です@<fn>{cb05k}。
//footnote[cb05k][これはパーサを再帰呼び出しすればいいだけなので、そんなに難しくはないはずなのですが。]

ただし、ノート（「@<code>$//note$」）と引用（「@<code>$//quote$」）だけはStarterで回避策を用意しました。

 * ノートなら、「@<code>$//note{$ ... @<code>$//}$」のかわりに「@<code>$====[note]$ ... @<code>$====[/note]$」を使ってください。
 * 引用なら、「@<code>$//quote{$ ... @<code>$//}$」のかわりに「@<code>$====[quote]$ ... @<code>$====[/quote]$」を使ってください。

これで、内部に別のブロックを含めることができます。

//emlist[サンプル]{
====[note] ■ノートの中にソースコード

ただし現在の制限として、キャプションをつけるとデザインが崩れるので、つけないこと。

@<code>$//$emlist{
print("Hello, World!")
@<code>$//$}

====[/note]
//}

//noindent
@<em>{表示結果：}@<br>{}

====[note] ■ノートの中にソースコード

ただし現在の制限として、キャプションをつけるとデザインが崩れるので、つけないこと。

//emlist{
print("Hello, World!")
//}

====[/note]

//blankline



ノートや引用以外の場合は、とりあえずの回避策として外側のブロックの@<LaTeX>{}コードを「@<code>$//embed$」で埋め込む方法があります。
次の例を参考にしてください。

//emlist[サンプル]{
@<code>$//$embed[latex]{
\begin{starternote}{■サンプル}  % 「//note{」のLaTeXコード
@<code>$//$}

ノートの中にソースコードを埋めるハック。

@<code>$//$emlist{
print("Hello, world!")
@<code>$//$}

@<code>$//$embed[latex]{
\end{starternote}  % 「//}」のLaTeXコード
@<code>$//$}
//}

//noindent
@<em>{表示結果：}@<br>{}

//embed[latex]{
\begin{starternote}{■サンプル}  % 「//note{」のLaTeXコード
//}

ノートの中にソースコードを埋めるハック。

//emlist{
print("Hello, world!")
//}

//embed[latex]{
\end{starternote}  % 「//}」のLaTeXコード
//}

//blankline




==={subsec-faq-block2} ブロックの中に箇条書きを入れても反映されないよ？

Re:VIEWの仕様です。

Re:VIEWでは、たとえば「@<code>$//note{$ ... @<code>$//}$」の中に「 * 項目1」のような箇条書きを入れても、箇条書きとして解釈されません。
これはかなり困った仕様です@<fn>{0nhax}。
//footnote[0nhax][これもパーサを再帰呼び出しすればいいだけのはずです。]

ただし、ノート（「@<code>$//note$」）と引用（「@<code>$//quote$」）だけはStarterで回避策を用意しました。

 * ノートなら、「@<code>$//note{$ ... @<code>$//}$」のかわりに「@<code>$====[note]$ ... @<code>$====[/note]$」を使ってください。
 * 引用なら、「@<code>$//quote{$ ... @<code>$//}$」のかわりに「@<code>$====[quote]$ ... @<code>$====[/quote]$」を使ってください。

これで、内部に箇条書きを含めることができます。

//emlist[サンプル]{
====[note] ■ノートの中に箇条書きやソースコードを入れる例

 * 項目1
 * 項目2

====[/note]
//}

//noindent
@<em>{表示結果：}@<br>{}

====[note] ■ノートの中に箇条書きやソースコードを入れる例

 * 項目1
 * 項目2

====[/note]

//blankline



ノートや引用ではないブロックの場合は、とりあえずの回避策として外側のブロックの@<LaTeX>{}コードを「@<code>$//embed$」で埋め込むのがいいでしょう。
次の例を参考にしてください。

//emlist[サンプル]{
@<code>$//$embed[latex]{
\begin{starternote}{■サンプル}  % 「//note{」のLaTeXコード
@<code>$//$}

ノートの中に箇条書きを含めるハック。

 * 項目1
 * 項目2

@<code>$//$embed[latex]{
\end{starternote}  % 「//}」のLaTeXコード
@<code>$//$}
//}

//noindent
@<em>{表示結果：}@<br>{}

//embed[latex]{
\begin{starternote}{■サンプル}  % 「//note{」のLaTeXコード
//}

ノートの中に箇条書きを含めるハック。

 * 項目1
 * 項目2

//embed[latex]{
\end{starternote}  % 「//}」のLaTeXコード
//}

//blankline




==={subsec-faq-memo} 「@<code>$//info{$ ... @<code>$//}$」のキャプションに「■メモ：」がつくんだけど？

Re:VIEWの仕様です。
「@<code>$//info$」だけでなく、他の「@<code>$//tip$」や「@<code>$//info$」や「@<code>$//warning$」や「@<code>$//important$」や「@<code>$//caution$」や「@<code>$//notice$」も、すべて「■メモ：」になります！

//emlist[サンプル]{
@<code>$//$memo[memoサンプル]{
@<code>$//$}
//}

//noindent
@<em>{表示結果：}@<br>{}

//memo[memoサンプル]{
//}

//blankline


//emlist[サンプル]{
@<code>$//$tip[tipサンプル]{
@<code>$//$}
//}

//noindent
@<em>{表示結果：}@<br>{}

//tip[tipサンプル]{
//}

//blankline


//emlist[サンプル]{
@<code>$//$info[infoサンプル]{
@<code>$//$}
//}

//noindent
@<em>{表示結果：}@<br>{}

//info[infoサンプル]{
//}

//blankline


//emlist[サンプル]{
@<code>$//$warning[warningサンプル]{
@<code>$//$}
//}

//noindent
@<em>{表示結果：}@<br>{}

//warning[warningサンプル]{
//}

//blankline


//emlist[サンプル]{
@<code>$//$important[importantサンプル]{
@<code>$//$}
//}

//noindent
@<em>{表示結果：}@<br>{}

//important[importantサンプル]{
//}

//blankline


//emlist[サンプル]{
@<code>$//$caution[cautionサンプル]{
@<code>$//$}
//}

//noindent
@<em>{表示結果：}@<br>{}

//caution[cautionサンプル]{
//}

//blankline


//emlist[サンプル]{
@<code>$//$notice[noticeサンプル]{
@<code>$//$}
//}

//noindent
@<em>{表示結果：}@<br>{}

//notice[noticeサンプル]{
//}

//blankline



わけがわからないよ。

これらのかわりに、Starterでは「@<code>$//note{$ ... @<code>$//}$」を使ってください。
詳しくは@<secref>{chap01-starter|subsec-ext-note}を参照のこと。


== ソースコード

=== コラム中のソースコードがページまたぎしてくれないよ？

仕様です。
ブロックと違い、コラム（「@<code>$==[column]$ ... @<code>$==[/column]$」）の中にはブロックを入れられますが、たとえばソースコードを入れた場合、ページをまたぐことができません。
これは@<LaTeX>{}のframed環境による制限です。


=== ソースコードを別ファイルから読み込む方法はないの？

@<href>{https://github.com/kmuto/review/issues/887}によると、このような方法でできるようです。

//emlist[別ファイルのソースコード(source/fib1.rb)を読み込む方法]{
@<code>$//$list[fib1][フィボナッチ数列]{
@<code>$@$<include>{source/fib1.rb}
@<code>$//$}
//}

ただし先のリンクにあるように、この方法はundocumentedであり、将来も機能が提供されるかは不明です。
「直近の締切りに間に合えばよい」「バージョンアップはしない」という場合のみ、割り切って使いましょう。
もし使えなくなったとしても、開発チームに苦情を申し立てないようお願いします。


== コンパイル

=== なんで@<LaTeX>{}のコンパイルがいつも3回実行されるの？

Re:VIEWの仕様です。
@<LaTeX>{}のコンパイル中にページ番号が変わってしまうと、古いページ番号のままPDFが生成されてしまいます。
このような事態を防ぐために、3回コンパイルしているのだと思われます@<fn>{wm3r8}。
//footnote[wm3r8][本当ならコンパイルの前後でauxファイルを比較して、ページ番号に差異があればもう一度コンパイルする、という方法が望ましいですが、そこまではしていないようです。]

なお@<LaTeX>{}のコンパイルには1秒程度しかかからないはずです。
3回繰り返しても、5秒未満でしょう。
時間がかかるのはそのあとのPDFへの変換であり、これは画像のサイズやファイル数に比例して時間がかかります。


=== コンパイルに時間かかりすぎ。もっと速くできない？

前の節で説明したように、時間がかかるのは@<LaTeX>{}のコンパイルではなく、そのあとのPDF生成です。
そしてPDF生成は、画像のサイズやファイル数に比例して時間がかかります。

画像のファイル数は減らせないので、かわりに画像のサイズを減らしたり、執筆中だけダミー画像で置き換えるのがいいでしょう。
詳しくは『ワンストップ！技術同人誌を書こう』という本の第8章を参照してください。

または、@<em>{config.yml}の「@<code>$dvioptions:$」の値を調整してください。
「@<code>$-z 1$」だと圧縮率は低いけど速くなり、「@<code>$-z 9$」だと圧縮率は高いけど遅くなります。


== タイトルページ（大扉）

=== タイトルが長いので、指定した箇所で改行したいんだけど？

長いタイトルをつけると、タイトルページ（「大扉」といいます）でタイトルが変な箇所で改行されてしまいます。

表示例：

//embed[latex]{
\begin{center}
  \gtfamily\sffamily\bfseries\ebseries\Huge
  週末なにしてますか?
  忙しいですか?
  金魚すくってもらっていいですか?
\end{center}
\bigskip
//}

この問題に対処するために、Starterではタイトル名に改行を含められるようになっています。
@<em>{config.yml}の「@<code>{booktitle: |-}」という箇所@<fn>{rsjp9}に、タイトル名を複数行で指定してください。
//footnote[rsjp9][「@<code>{|-}」は、YAMLにおいて複数行を記述する記法の1つ（最後の行の改行は捨てられる）。]

//emlist[サンプル]{
booktitle: |-
  週末なにしてますか?
  忙しいですか?
  金魚すくってもらっていいですか?
//}

こうすると、タイトルページでも複数行のまま表示されます。

表示例：

//embed[latex]{
\begin{center}
  \gtfamily\sffamily\bfseries\ebseries\Huge
  週末なにしてますか?\\
  忙しいですか?\\
  金魚すくってもらっていいですか?\par
\end{center}
\bigskip
//}

同様に、サブタイトルも複数行で指定できます。

ただし本の最後のページにある「奥付」では、タイトルもサブタイトルも改行されずに表示されます。

Starterではなく、素のRe:VIEWやTechboosterのテンプレートを使っている場合は、@<em>{layouts/layout.tex.erb}を変更します。
変更するまえに、@<em>{layouts/layout.tex.erb}のバックアップをとっておくといいでしょう。

//emlist[layouts/layout.tex.erb][ruby]{
....(省略)....
\thispagestyle{empty}
\begin{center}%
  \mbox{} \vskip5zw
   \reviewtitlefont%
    @<del>${\HUGE\bfseries <%= escape_latex(@config.name_of("booktitle")) %> \par}%$
    @<b>${\HUGE\bfseries 週末なにしてますか?\newline%$
    @<b>$                忙しいですか?\newline%$
    @<b>$                金魚すくってもらっていいですか?\par}%$
....(省略)....
//}


=== タイトルぺージがださい。もっとかっこよくならない？

@<LaTeX>{}を使ってるかぎりは難しいでしょう。
それよりもPhotoshopやKeynoteを使ってタイトルページを作るほうが簡単です（@<img>{titlepage-samples}）。

//image[titlepage-samples][Keynoteを使って作成したタイトルページの例]

タイトルページをPhotoshopやKeynoteで作る場合は、@<em>{config.yml}で「@<code>$titlepage: false$」を指定し、タイトルページを生成しないようにしましょう。
そのあと、別途作成したタイトルページのPDFファイルと「@<em>$rake pdf$」で生成されたPDFファイルとを結合してください。

なお奥付もPhotoshopやKeynoteで作る場合は、@<em>{config.yml}に「@<code>$colophon: false$」を指定し、奥付を生成しないようにしてください。
また@<em>{config.yml}には「@<code>$colophon:$」の設定箇所が2箇所あるので、ファイルの下のほうにある該当箇所を変更してください。


== その他

=== 設定ファイルをいじったら、動かなくなった！

Re:VIEWの設定ファイルである@<em>{config.yml}や@<em>{catalog.yml}は、「YAML」というフォーマットで記述されています。
このフォーマットに違反すると、設定ファイルが読み込めなくなるため、エラーになります。

「YAML」のフォーマットについての詳細はGoogle検索してください。
ありがちなミスを以下に挙げておきます。

 * タブ文字を使うと、エラーになります。かわりに半角スペースを使ってください。
 * 全角スペースを使うと、エラーになります。かわりに半角スペースを使ってください。
 * 「@<code>{:}」のあとに半角スペースが必要です。たとえば@<br>{}
   「@<tt>{titlepage:false}」はダメです。@<br>{}
   「@<tt>{titlepage: false}」のように書いてください。
 * 「@<code>{,}」のあとに半角スペースが必要です。たとえば@<br>{}
   「@<code>{texstyle: [reviewmacro,starter,mystyle]}」はダメです。@<br>{}
   「@<code>{texstyle: [reviewmacro, starter, mystyle]}」のように書いてください。
 * インデントが揃ってないと、エラーになります。
   たとえば@<em>{catalog.yml}が次のようになっていると、インデントが揃ってないのでエラーになります。

//emlist[「CHAPS:」のインデントが揃ってないのでエラー]{
PREDEF:
  - chap00-preface.re

CHAPS:
   - chap01-starter.re
  - chap02-faq.re

APPENDIX:

POSTDEF:
  - chap99-postscript.re
//}

 * 「@<em>{-}」のあとに半角スペースが必要です。たとえば上の例で@<br>{}
   「@<code>{- chap01-starter.re}」が@<br>{}
   「@<code>{-chap01-starter.re}」となっていると、エラーになります。


=== 印刷用とタブレット用で設定を少し変えるにはどうするの？

Re:VIEWにはそのような機能がありませんので、自力で頑張る必要があります。

方針としては、設定ファイルやスタイルファイルを用途に応じて都度生成するといいでしょう。
具体的には次のようにします。

//blankline
//noindent
(1) まず少し変えたいファイルの名前を変更し、末尾に「@<em>{.eruby}」をつけます。

//cmd{
$ mv config.yml         config.yml.eruby
$ mv sty/mytextsize.sty sty/mytextsize.sty.eruby
$ mv sty/starter.sty    sty/starter.sty.eruby
## またはこうでもよい
$ mv config.yml{,.eruby}
$ mv sty/mytextsize.sty{,.eruby}
$ mv sty/starter.sty{,.eruby}
//}

//noindent
(2) 次に、それらのファイルに次のような条件分岐を埋め込みます。

//source[config.yml.eruby]{
....(省略)....
@<b>$<% if buildmode == 'printing'   # 印刷向け %>$
texdocumentclass: ["jsbook", "uplatex,papersize,twoside,b5j,10pt,openright"]
@<b>$<% elsif buildmode == 'tablet'  # タブレット向け %>$
texdocumentclass: ["jsbook", "uplatex,papersize,oneside,a5j,10pt,openany"]
@<b>$<% else abort "error: buildmode=#{buildmode.inspect}" %>$
@<b>$<% end %>$
....(省略)....
@<b>$<% if buildmode == 'printing'   # 印刷向け %>$
dvioptions: "-d 5 -z 3"  # 速度優先
@<b>$<% elsif buildmode == 'tablet'  # タブレット向け %>$
dvioptions: "-d 5 -z 9"  # 圧縮率優先
@<b>$<% else abort "error: buildmode=#{buildmode.inspect}" %>$
@<b>$<% end %>$
....(省略)....
//}

//source[sty/mytextsize.sty.eruby]{
@<b>$<%$
@<b>$if buildmode == 'printing'   # 印刷向け$
@<b>$  textwidth  = '42zw'$
@<b>$  sidemargin = '1zw'$
@<b>$elsif buildmode == 'tablet'  # タブレット向け$
@<b>$  textwidth  = '40zw'$
@<b>$  sidemargin = '0zw'$
@<b>$else abort "error: buildmode=#{buildmode.inspect}"$
@<b>$end$
@<b>$%>$
....(省略)....
\setlength{\textwidth}{@<b>$<%= textwidth %>$}
....(省略)....
\addtolength{\oddsidemargin}{@<b>$<%= sidemargin %>$}
\addtolength{\evensidemargin}{-@<b>$<%= sidemargin %>$}
....(省略)....
//}

//source[sty/starter.sty.eruby]{
....(省略)....
@<b>$<% if buildmode == 'printing'   # 印刷向け %>$
\definecolor{starter@chaptercolor}{gray}{0.40}  % 0.0: black, 1.0: white
\definecolor{starter@sectioncolor}{gray}{0.40}
\definecolor{starter@captioncolor}{gray}{0.40}
\definecolor{starter@quotecolor}{gray}{0.40}
@<b>$<% elsif buildmode == 'tablet'  # タブレット向け %>$
\definecolor{starter@chaptercolor}{HTML}{20B2AA} % lightseagreen
\definecolor{starter@sectioncolor}{HTML}{20B2AA} % lightseagreen
\definecolor{starter@captioncolor}{HTML}{FFA500} % orange
\definecolor{starter@quotecolor}{HTML}{E6E6FA}   % lavender
@<b>$<% else abort "error: buildmode=#{buildmode.inspect}" %>$
@<b>$<% end %>$
....(省略)....
@<b>$<% if buildmode == 'printing'   # 印刷向け %>$
\hypersetup{colorlinks=true,linkcolor=black} % 黒
@<b>$<% elsif buildmode == 'tablet'  # タブレット向け %>$
\hypersetup{colorlinks=true,linkcolor=blue}  % 青
@<b>$<% else abort "error: buildmode=#{buildmode.inspect}" %>$
@<b>$<% end %>$
//}

//noindent
(3) ファイルを生成するRakeタスクを定義します。
ここまでが準備です。

//source[lib/tasks/mytasks.rake]{
def render_eruby_files(param)   # 要 Ruby >= 2.2
  Dir.glob('**/*.eruby').each do |erubyfile|
    origfile = erubyfile.sub(/\.eruby$/, '')
    sh "erb -T 2 '#{param}' #{erubyfile} > #{origfile}"
  end
end


namespace :setup do

  desc "*印刷用に設定 (B5, 10pt, mono)"
  task :printing do
    render_eruby_files('buildmode=printing')
  end

  desc "*タブレット用に設定 (A5, 10pt, color)"
  task :tablet do
    render_eruby_files('buildmode=tablet')
  end

end
//}

//noindent
(4)「@<em>{rake setup::printing}」または「@<em>{rake setup::tablet}」を実行します。
すると、@<em>{config.yml}と@<em>{sty/mytextsize.sty}と@<em>{sty/starter.sty}が生成されます。
そのあとで「@<em>{rake pdf}」を実行すれば、用途に応じたPDFが生成されます。

//cmd{
$ @<b>$rake setup::printing  # 印刷用$
$ rake pdf
$ mv mybook.pdf mybook_printing.pdf

$ @<b>$rake setup::tablet    # タブレット用$
$ rake pdf
$ mv mybook.pdf mybook_tablet.pdf
//}
