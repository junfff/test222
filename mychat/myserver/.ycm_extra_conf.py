# This file is NOT licensed under the GPLv3, which is the license for the rest

# of YouCompleteMe.

#

# Here's the license text for this file:

#

# This is free and unencumbered software released into the public domain.

#

# Anyone is free to copy, modify, publish, use, compile, sell, or

# distribute this software, either in source code form or as a compiled

# binary, for any purpose, commercial or non-commercial, and by any

# means.

#

# In jurisdictions that recognize copyright laws, the author or authors

# of this software dedicate any and all copyright interest in the

# software to the public domain. We make this dedication for the benefit

# of the public at large and to the detriment of our heirs and

# successors. We intend this dedication to be an overt act of

# relinquishment in perpetuity of all present and future rights to this

# software under copyright law.

#

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,

# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF

# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.

# IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR

# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,

# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR

# OTHER DEALINGS IN THE SOFTWARE.

#

# For more information, please refer to <http://unlicense.org/>

import os

import ycm_core

# These are the compilation flags that will be used in case there's no

# compilation database set (by default, one is not set).

# CHANGE THIS LIST OF FLAGS. YES, THIS IS THE DROID YOU HAVE BEEN LOOKING FOR.

flags = [

'-x', 'c++',

'-Wall',

'-Wextra',

'-fPIE',

'-D_REENTRANT',

'-std=c++1y',

'-stdlib=libc++',

'-ftemplate-depth=8192',

'-fconstexpr-depth=8192',

'-lc++abi',

'-isystem', '/usr/include/c++/v1',

'-isystem', '/usr/local/include',

'-isystem', '/usr/include/x86_64-linux-gnu',

'-isystem', '/usr/include',

'-I', '/usr/local/src/yeppp/1.0.0/library/headers',

'-I', '/usr/local/src/string_view/include/experimental',

'-I', '/usr/local/src/scoped_resource',

'-I', '/usr/local/include/hpx/external',

'-I', '/opt/qt/5.2.2/linux/mkspecs/linux-clang-libc++',

'-I', '/opt/qt/5.2.2/linux/include',

'-I', '/opt/qt/5.2.2/linux/include/QtBluetooth',

'-I', '/opt/qt/5.2.2/linux/include/QtCLucene',

'-I', '/opt/qt/5.2.2/linux/include/QtConcurrent',

'-I', '/opt/qt/5.2.2/linux/include/QtCore',

'-I', '/opt/qt/5.2.2/linux/include/QtDBus',

'-I', '/opt/qt/5.2.2/linux/include/QtDeclarative',

'-I', '/opt/qt/5.2.2/linux/include/QtDesigner',

'-I', '/opt/qt/5.2.2/linux/include/QtDesignerComponents',

'-I', '/opt/qt/5.2.2/linux/include/QtGui',

'-I', '/opt/qt/5.2.2/linux/include/QtHelp',

'-I', '/opt/qt/5.2.2/linux/include/QtMultimedia',

'-I', '/opt/qt/5.2.2/linux/include/QtMultimediaQuick_p',

'-I', '/opt/qt/5.2.2/linux/include/QtMultimediaWidgets',

'-I', '/opt/qt/5.2.2/linux/include/QtNetwork',

'-I', '/opt/qt/5.2.2/linux/include/QtNfc',

'-I', '/opt/qt/5.2.2/linux/include/QtOpenGL',

'-I', '/opt/qt/5.2.2/linux/include/QtOpenGLExtensions',

'-I', '/opt/qt/5.2.2/linux/include/QtPlatformSupport',

'-I', '/opt/qt/5.2.2/linux/include/QtPositioning',

'-I', '/opt/qt/5.2.2/linux/include/QtPrintSupport',

'-I', '/opt/qt/5.2.2/linux/include/QtQml',

'-I', '/opt/qt/5.2.2/linux/include/QtQuick',

'-I', '/opt/qt/5.2.2/linux/include/QtQuickParticles',

'-I', '/opt/qt/5.2.2/linux/include/QtQuickTest',

'-I', '/opt/qt/5.2.2/linux/include/QtScript',

'-I', '/opt/qt/5.2.2/linux/include/QtScriptTools',

'-I', '/opt/qt/5.2.2/linux/include/QtSensors',

'-I', '/opt/qt/5.2.2/linux/include/QtSerialPort',

'-I', '/opt/qt/5.2.2/linux/include/QtSql',

'-I', '/opt/qt/5.2.2/linux/include/QtSvg',

'-I', '/opt/qt/5.2.2/linux/include/QtTest',

'-I', '/opt/qt/5.2.2/linux/include/QtUiTools',

'-I', '/opt/qt/5.2.2/linux/include/QtWebKit',

'-I', '/opt/qt/5.2.2/linux/include/QtWebKitWidgets',

'-I', '/opt/qt/5.2.2/linux/include/QtWidgets',

'-I', '/opt/qt/5.2.2/linux/include/QtX11Extras',

'-I', '/opt/qt/5.2.2/linux/include/QtXml',

'-I', '/opt/qt/5.2.2/linux/include/QtXmlPatterns',
'-I', '/home/ljf/learn/mychat/myserver/include',
]

# Set this to the absolute path to the folder (NOT the file!) containing the

# compile_commands.json file to use that instead of 'flags'. See here for

# more details: http://clang.llvm.org/docs/JSONCompilationDatabase.html

#

# Most projects will NOT need to set this to anything; you can just change the

# 'flags' list of compilation flags. Notice that YCM itself uses that approach.

compilation_database_folder = ''

if os.path.exists( compilation_database_folder ):

  database = ycm_core.CompilationDatabase( compilation_database_folder )

else:

  database = None

SOURCE_EXTENSIONS = [ '.cpp', '.cxx', '.cc', '.c', '.m', '.mm' ]

def DirectoryOfThisScript():

  return os.path.dirname( os.path.abspath( __file__ ) )

def MakeRelativePathsInFlagsAbsolute( flags, working_directory ):

  if not working_directory:

    return list( flags )

  new_flags = []

  make_next_absolute = False

  path_flags = [ '-isystem', '-I', '-iquote', '--sysroot=' ]

  for flag in flags:

    new_flag = flag

    if make_next_absolute:

      make_next_absolute = False

      if not flag.startswith( '/' ):

        new_flag = os.path.join( working_directory, flag )

    for path_flag in path_flags:

      if flag == path_flag:

        make_next_absolute = True

        break

      if flag.startswith( path_flag ):

        path = flag[ len( path_flag ): ]

        new_flag = path_flag + os.path.join( working_directory, path )

        break

    if new_flag:

      new_flags.append( new_flag )

  return new_flags

def IsHeaderFile( filename ):

  extension = os.path.splitext( filename )[ 1 ]

  return extension in [ '.h', '.hxx', '.hpp', '.hh' ]

def GetCompilationInfoForFile( filename ):

  # The compilation_commands.json file generated by CMake does not have entries

  # for header files. So we do our best by asking the db for flags for a

  # corresponding source file, if any. If one exists, the flags for that file

  # should be good enough.

  if IsHeaderFile( filename ):

    basename = os.path.splitext( filename )[ 0 ]

    for extension in SOURCE_EXTENSIONS:

      replacement_file = basename + extension

      if os.path.exists( replacement_file ):

        compilation_info = database.GetCompilationInfoForFile(

          replacement_file )

        if compilation_info.compiler_flags_:

          return compilation_info

    return None

  return database.GetCompilationInfoForFile( filename )

def FlagsForFile( filename, **kwargs ):

  if database:

    # Bear in mind that compilation_info.compiler_flags_ does NOT return a

    # python list, but a "list-like" StringVec object

    compilation_info = GetCompilationInfoForFile( filename )

    if not compilation_info:

      return None

    final_flags = MakeRelativePathsInFlagsAbsolute(

      compilation_info.compiler_flags_,

      compilation_info.compiler_working_dir_ )

  else:

    relative_to = DirectoryOfThisScript()

    final_flags = MakeRelativePathsInFlagsAbsolute( flags, relative_to )

  return {

    'flags': final_flags,

    'do_cache': True

  }
