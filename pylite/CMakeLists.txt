cmake_minimum_required(VERSION 3.10)
project(pylite C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Enable C language for FFI checks
enable_language(C)

# Source files
set(SOURCES
    main.cpp
    src/stdlibs/builtins.cpp
    src/stdlibs/string.cpp
    src/stdlibs/re.cpp
    src/stdlibs/difflib.cpp
    src/stdlibs/textwrap.cpp
    src/stdlibs/unicodedata.cpp
    src/stdlibs/stringprep.cpp
    src/stdlibs/readline.cpp
    src/stdlibs/rlcompleter.cpp
    src/stdlibs/struct.cpp
    src/stdlibs/codecs.cpp
    src/stdlibs/datetime.cpp
    src/stdlibs/zoneinfo.cpp
    src/stdlibs/calendar.cpp
    src/stdlibs/collections.cpp
    src/stdlibs/collections_abc.cpp
    src/stdlibs/heapq.cpp
    src/stdlibs/bisect.cpp
    src/stdlibs/array.cpp
    src/stdlibs/weakref.cpp
    src/stdlibs/types.cpp
    src/stdlibs/copy.cpp
    src/stdlibs/pprint.cpp
    src/stdlibs/reprlib.cpp
    src/stdlibs/enum.cpp
    src/stdlibs/graphlib.cpp
    src/stdlibs/numbers.cpp
    src/stdlibs/math.cpp
    src/stdlibs/cmath.cpp
    src/stdlibs/decimal.cpp
    src/stdlibs/fractions.cpp
    src/stdlibs/random.cpp
    src/stdlibs/statistics.cpp
    src/stdlibs/itertools.cpp
    src/stdlibs/functools.cpp
    src/stdlibs/operator.cpp
    src/stdlibs/pathlib.cpp
    src/stdlibs/os_path.cpp
    src/stdlibs/stat.cpp
    src/stdlibs/filecmp.cpp
    src/stdlibs/tempfile.cpp
    src/stdlibs/glob.cpp
    src/stdlibs/fnmatch.cpp
    src/stdlibs/linecache.cpp
    src/stdlibs/shutil.cpp
    src/stdlibs/pickle.cpp
    src/stdlibs/copyreg.cpp
    src/stdlibs/shelve.cpp
    src/stdlibs/marshal.cpp
    src/stdlibs/dbm.cpp
    src/stdlibs/sqlite3.cpp
    src/stdlibs/zlib.cpp
    src/stdlibs/gzip.cpp
    src/stdlibs/bz2.cpp
    src/stdlibs/lzma.cpp
    src/stdlibs/zipfile.cpp
    src/stdlibs/tarfile.cpp
    src/stdlibs/csv.cpp
    src/stdlibs/configparser.cpp
    src/stdlibs/tomllib.cpp
    src/stdlibs/netrc.cpp
    src/stdlibs/plistlib.cpp
    src/stdlibs/hashlib.cpp
    src/stdlibs/hmac.cpp
    src/stdlibs/secrets.cpp
    src/stdlibs/os.cpp
    src/stdlibs/io.cpp
    src/stdlibs/time.cpp
    src/stdlibs/logging.cpp
    src/stdlibs/logging_config.cpp
    src/stdlibs/logging_handlers.cpp
    src/stdlibs/platform.cpp
    src/stdlibs/errno.cpp
    src/stdlibs/ctypes.cpp
    src/stdlibs/argparse.cpp
    src/stdlibs/optparse.cpp
    src/stdlibs/getpass.cpp
    src/stdlibs/fileinput.cpp
    src/stdlibs/curses.cpp
    src/stdlibs/curses_textpad.cpp
    src/stdlibs/curses_ascii.cpp
    src/stdlibs/curses_panel.cpp
    src/stdlibs/threading.cpp
    src/stdlibs/multiprocessing.cpp
    src/stdlibs/multiprocessing_shared_memory.cpp
    src/stdlibs/concurrent_futures.cpp
    src/stdlibs/subprocess.cpp
    src/stdlibs/sched.cpp
    src/stdlibs/queue.cpp
    src/stdlibs/contextvars.cpp
    src/stdlibs/_thread.cpp
    src/stdlibs/asyncio.cpp
    src/stdlibs/socket.cpp
    src/stdlibs/ssl.cpp
    src/stdlibs/select.cpp
    src/stdlibs/selectors.cpp
    src/stdlibs/signal.cpp
    src/stdlibs/mmap.cpp
    src/stdlibs/email.cpp
    src/stdlibs/json.cpp
    src/stdlibs/mailbox.cpp
    src/stdlibs/mimetypes.cpp
    src/stdlibs/base64.cpp
    src/stdlibs/binascii.cpp
    src/stdlibs/quopri.cpp
    src/stdlibs/html.cpp
    src/stdlibs/html_parser.cpp
    src/stdlibs/html_entities.cpp
    src/stdlibs/xml_etree_ElementTree.cpp
    src/stdlibs/xml_dom.cpp
    src/stdlibs/xml_dom_minidom.cpp
    src/stdlibs/xml_dom_pulldom.cpp
    src/stdlibs/xml_sax.cpp
    src/stdlibs/xml_sax_handler.cpp
    src/stdlibs/xml_sax_saxutils.cpp
    src/stdlibs/xml_sax_xmlreader.cpp
    src/stdlibs/xml_parsers_expat.cpp
    src/stdlibs/webbrowser.cpp
    src/stdlibs/wsgiref.cpp
    src/stdlibs/urllib.cpp
    src/stdlibs/urllib_request.cpp
    src/stdlibs/urllib_response.cpp
    src/stdlibs/urllib_parse.cpp
    src/stdlibs/urllib_error.cpp
    src/stdlibs/urllib_robotparser.cpp
    src/stdlibs/http.cpp
    src/stdlibs/http_client.cpp
    src/stdlibs/ftplib.cpp
    src/stdlibs/poplib.cpp
    src/stdlibs/imaplib.cpp
    src/stdlibs/smtplib.cpp
    src/stdlibs/uuid.cpp
    src/stdlibs/socketserver.cpp
    src/stdlibs/http_server.cpp
    src/stdlibs/http_cookies.cpp
    src/stdlibs/http_cookiejar.cpp
    src/stdlibs/xmlrpc.cpp
    src/stdlibs/xmlrpc_client.cpp
    src/stdlibs/xmlrpc_server.cpp
    src/stdlibs/ipaddress.cpp
    src/stdlibs/wave.cpp
    src/stdlibs/colorsys.cpp
    src/stdlibs/gettext.cpp
    src/stdlibs/locale.cpp
    src/stdlibs/turtle.cpp
    src/stdlibs/cmd.cpp
    src/stdlibs/shlex.cpp
    src/stdlibs/tkinter.cpp
    src/stdlibs/tkinter_colorchooser.cpp
    src/stdlibs/tkinter_font.cpp
    src/stdlibs/tkinter_messagebox.cpp
    src/stdlibs/tkinter_scrolledtext.cpp
    src/stdlibs/tkinter_dnd.cpp
    src/stdlibs/tkinter_ttk.cpp
    src/stdlibs/idle.cpp
    src/stdlibs/typing.cpp
    src/stdlibs/pydoc.cpp
    src/stdlibs/doctest.cpp
    src/stdlibs/unittest.cpp
    src/stdlibs/unittest_mock.cpp
    src/stdlibs/test.cpp
    src/stdlibs/test_support.cpp
    src/stdlibs/test_support_socket_helper.cpp
    src/stdlibs/test_support_script_helper.cpp
    src/stdlibs/test_support_bytecode_helper.cpp
    src/stdlibs/test_support_threading_helper.cpp
    src/stdlibs/test_support_os_helper.cpp
    src/stdlibs/test_support_import_helper.cpp
    src/stdlibs/test_support_warnings_helper.cpp
    src/stdlibs/bdb.cpp
    src/stdlibs/faulthandler.cpp
    src/stdlibs/pdb.cpp
    src/stdlibs/timeit.cpp
    src/stdlibs/trace.cpp
    src/stdlibs/tracemalloc.cpp
    src/stdlibs/ensurepip.cpp
    src/stdlibs/venv.cpp
    src/stdlibs/zipapp.cpp
    src/stdlibs/sys.cpp
    src/stdlibs/sys_monitoring.cpp
    src/stdlibs/sysconfig.cpp
    src/stdlibs/__main__.cpp
    src/stdlibs/warnings.cpp
    src/stdlibs/dataclasses.cpp
    src/stdlibs/contextlib.cpp
    src/stdlibs/abc.cpp
    src/stdlibs/atexit.cpp
    src/stdlibs/traceback.cpp
    src/stdlibs/__future__.cpp
    src/stdlibs/gc.cpp
    src/stdlibs/inspect.cpp
    src/stdlibs/site.cpp
    src/stdlibs/code.cpp
    src/stdlibs/codeop.cpp
    src/stdlibs/zipimport.cpp
    src/stdlibs/pkgutil.cpp
    src/stdlibs/modulefinder.cpp
    src/stdlibs/runpy.cpp
    src/stdlibs/importlib.cpp
    src/stdlibs/importlib_resources.cpp
    src/stdlibs/importlib_resources_abc.cpp
    src/stdlibs/importlib_metadata.cpp
    src/stdlibs/ast.cpp
    src/stdlibs/symtable.cpp
    src/stdlibs/token.cpp
    src/stdlibs/keyword.cpp
    src/stdlibs/tokenize.cpp
    src/stdlibs/tabnanny.cpp
    src/stdlibs/pyclbr.cpp
    src/stdlibs/py_compile.cpp
    src/stdlibs/compileall.cpp
    src/stdlibs/dis.cpp
    src/stdlibs/pickletools.cpp
    src/stdlibs/msvcrt.cpp
    src/stdlibs/winreg.cpp
    src/stdlibs/winsound.cpp
    src/stdlibs/posix.cpp
    src/stdlibs/pwd.cpp
    src/stdlibs/grp.cpp
    src/stdlibs/termios.cpp
    src/stdlibs/tty.cpp
    src/stdlibs/pty.cpp
    src/stdlibs/fcntl.cpp
    src/stdlibs/resource.cpp
    src/stdlibs/syslog.cpp
    src/stdlibs/getopt.cpp
    src/stdlibs/set.cpp
    src/stdlibs/file.cpp
    src/stdlibs/network.cpp
)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Find dependencies
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

# Find libffi (used by LLVM)
find_library(FFI_LIBRARY NAMES ffi)
find_path(FFI_INCLUDE_DIR NAMES ffi.h)
if(FFI_LIBRARY AND FFI_INCLUDE_DIR)
    include_directories(${FFI_INCLUDE_DIR})
    message(STATUS "Found libffi: ${FFI_LIBRARY}")
else()
    message(STATUS "libffi not found - trying to continue without it")
endif()

# Find ncurses/terminfo
find_library(TERMINFO_LIBRARY NAMES tinfo terminfo ncurses)
if(TERMINFO_LIBRARY)
    message(STATUS "Found terminfo: ${TERMINFO_LIBRARY}")
else()
    message(STATUS "terminfo not found - trying to continue without it")
endif()

# Find libxml2
find_package(LibXml2)
if(LIBXML2_FOUND)
    include_directories(${LIBXML2_INCLUDE_DIR})
    message(STATUS "Found LibXml2: ${LIBXML2_LIBRARIES}")
endif()

# Set simplified LLVM configuration - use only basic components to avoid dependency issues
set(LLVM_ENABLE_FFI OFF CACHE BOOL "LLVM FFI support")
set(LLVM_ENABLE_TERMINFO OFF CACHE BOOL "LLVM Terminfo support")
set(LLVM_ENABLE_LIBXML2 OFF CACHE BOOL "LLVM LibXml2 support")

# Find LLVM
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Include LLVM directories
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Generate executable
add_executable(pylite ${SOURCES})

# Optional: Add compiler-specific flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Add flags for GCC and Clang
    target_compile_options(pylite PRIVATE -Wall -Wextra -pedantic)
    # Note: RTTI is required for dynamic_cast used throughout the codebase
elseif(MSVC)
    # Add flags for MSVC
    target_compile_options(pylite PRIVATE /W4)
endif()

# Get proper LLVM shared libraries with minimal dependencies
llvm_map_components_to_libnames(llvm_libs 
    Core 
    Support
    X86
    ExecutionEngine
    MCJIT
    BitReader
    BitWriter
    OrcJIT
)

# Link with required libraries and handle conditional dependencies
target_link_libraries(pylite ${CURL_LIBRARIES})
target_link_libraries(pylite ${llvm_libs})

# Add optional libraries if found
if(FFI_LIBRARY)
    target_link_libraries(pylite ${FFI_LIBRARY})
endif()

if(TERMINFO_LIBRARY)
    target_link_libraries(pylite ${TERMINFO_LIBRARY})
endif()

if(LIBXML2_FOUND)
    target_link_libraries(pylite ${LIBXML2_LIBRARIES})
endif()

# Platform-specific libraries
if(UNIX AND NOT APPLE)
    # Linux
    target_link_libraries(pylite stdc++fs dl)
elseif(APPLE)
    # macOS - no special libraries needed
elseif(WIN32)
    # Windows
    target_link_libraries(pylite psapi shell32)
endif()

# Installation rules
install(TARGETS pylite DESTINATION bin)

# Create a directory for examples
install(DIRECTORY examples/ DESTINATION share/pylite/examples)

# Output information
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
