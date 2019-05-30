
namespace 'starter' do

  desc "* generate files from *.eruby"
  task 'gen' do
    bases = ["config.yml", "catalog.yml", "sty/mytextsize.sty", "sty/starter.sty"]
    for x in bases
      sh "baby_erubis -f context.json #{x}.eruby > #{x}"
    end
  end

  desc "* copy files to kauplan.org"
  task 'deploy' do
    require 'fileutils'
    files = []
    File.open('MANIFEST').each_line do |line|
      files << line.strip() unless line.start_with?('#')
    end
    destdir = "~/src/kauplan.org/data/reviewstarter/baseproject"
    destdir = File.expand_path(destdir)
    FileUtils.rm_rf(Dir.glob("#{destdir}/*"))
    files.each do |file|
      dir = File.join(destdir, File.dirname(file))
      FileUtils.mkdir_p(dir) unless File.directory?(dir)
      FileUtils.cp([file], dir)
    end
  end

end
