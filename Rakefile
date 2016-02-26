require 'rake/clean'

cxx    = ENV['CXX']
python = ENV['PYTHON_INCLUDE_PATH']

langflags = "-std=c++14"
wflags    = "-Wall -Wextra -pedantic -Wno-missing-field-initializers"
archflags = "-march=native"
incflags  = "-isystem #{python}"
libflags  = "-shared -fpic -fvisibility=hidden"
optflags  = "-O3 -flto"
cxxflags  = "#{langflags} #{wflags} #{archflags} #{incflags} #{libflags} #{optflags}"

targets = {'dummy/_dummy.so' => 'source/dummy.cpp'}

task :default => targets.keys

targets.each do |dst, src|
	file dst => [src] do
		sh "#{cxx} #{cxxflags} #{src} -o #{dst}"
	end
end

task :clobber do
	targets.keys.each{|f| File.delete(f)}
end
