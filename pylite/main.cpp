#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

#include "include/token.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/interpreter.h"
#include "include/error.h"
#include "include/builtins.h"

#include "include/stdlibs/builtins.h"
#include "include/stdlibs/string.h"
#include "include/stdlibs/re.h"
#include "include/stdlibs/difflib.h"
#include "include/stdlibs/textwrap.h"
#include "include/stdlibs/unicodedata.h"
#include "include/stdlibs/stringprep.h"
#include "include/stdlibs/readline.h"
#include "include/stdlibs/rlcompleter.h"
#include "include/stdlibs/struct.h"
#include "include/stdlibs/codecs.h"
#include "include/stdlibs/datetime.h"
#include "include/stdlibs/zoneinfo.h"
#include "include/stdlibs/calendar.h"
#include "include/stdlibs/collections.h"
#include "include/stdlibs/collections_abc.h"
#include "include/stdlibs/heapq.h"
#include "include/stdlibs/bisect.h"
#include "include/stdlibs/array.h"
#include "include/stdlibs/weakref.h"
#include "include/stdlibs/types.h"
#include "include/stdlibs/copy.h"
#include "include/stdlibs/pprint.h"
#include "include/stdlibs/reprlib.h"
#include "include/stdlibs/enum.h"
#include "include/stdlibs/graphlib.h"
#include "include/stdlibs/numbers.h"
#include "include/stdlibs/math.h"
#include "include/stdlibs/cmath.h"
#include "include/stdlibs/decimal.h"
#include "include/stdlibs/fractions.h"
#include "include/stdlibs/random.h"
#include "include/stdlibs/statistics.h"
#include "include/stdlibs/itertools.h"
#include "include/stdlibs/functools.h"
#include "include/stdlibs/operator.h"
#include "include/stdlibs/pathlib.h"
#include "include/stdlibs/os_path.h"
#include "include/stdlibs/stat.h"
#include "include/stdlibs/filecmp.h"
#include "include/stdlibs/tempfile.h"
#include "include/stdlibs/glob.h"
#include "include/stdlibs/fnmatch.h"
#include "include/stdlibs/linecache.h"
#include "include/stdlibs/shutil.h"
#include "include/stdlibs/pickle.h"
#include "include/stdlibs/copyreg.h"
#include "include/stdlibs/shelve.h"
#include "include/stdlibs/marshal.h"
#include "include/stdlibs/dbm.h"
#include "include/stdlibs/sqlite3.h"
#include "include/stdlibs/zlib.h"
#include "include/stdlibs/gzip.h"
#include "include/stdlibs/bz2.h"
#include "include/stdlibs/lzma.h"
#include "include/stdlibs/zipfile.h"
#include "include/stdlibs/tarfile.h"
#include "include/stdlibs/csv.h"
#include "include/stdlibs/configparser.h"
#include "include/stdlibs/tomllib.h"
#include "include/stdlibs/netrc.h"
#include "include/stdlibs/plistlib.h"
#include "include/stdlibs/hashlib.h"
#include "include/stdlibs/hmac.h"
#include "include/stdlibs/secrets.h"
#include "include/stdlibs/os.h"
#include "include/stdlibs/io.h"
#include "include/stdlibs/time.h"
#include "include/stdlibs/logging.h"
#include "include/stdlibs/logging_config.h"
#include "include/stdlibs/logging_handlers.h"
#include "include/stdlibs/platform.h"
#include "include/stdlibs/errno.h"
#include "include/stdlibs/ctypes.h"
#include "include/stdlibs/argparse.h"
#include "include/stdlibs/optparse.h"
#include "include/stdlibs/getpass.h"
#include "include/stdlibs/fileinput.h"
#include "include/stdlibs/curses.h"
#include "include/stdlibs/curses_textpad.h"
#include "include/stdlibs/curses_ascii.h"
#include "include/stdlibs/curses_panel.h"
#include "include/stdlibs/threading.h"
#include "include/stdlibs/multiprocessing.h"
#include "include/stdlibs/multiprocessing_shared_memory.h"
#include "include/stdlibs/concurrent_futures.h"
#include "include/stdlibs/subprocess.h"
#include "include/stdlibs/sched.h"
#include "include/stdlibs/queue.h"
#include "include/stdlibs/contextvars.h"
#include "include/stdlibs/_thread.h"
#include "include/stdlibs/asyncio.h"
#include "include/stdlibs/socket.h"
#include "include/stdlibs/ssl.h"
#include "include/stdlibs/select.h"
#include "include/stdlibs/selectors.h"
#include "include/stdlibs/signal.h"
#include "include/stdlibs/mmap.h"
#include "include/stdlibs/email.h"
#include "include/stdlibs/json.h"
#include "include/stdlibs/mailbox.h"
#include "include/stdlibs/mimetypes.h"
#include "include/stdlibs/base64.h"
#include "include/stdlibs/binascii.h"
#include "include/stdlibs/quopri.h"
#include "include/stdlibs/html.h"
#include "include/stdlibs/html_parser.h"
#include "include/stdlibs/html_entities.h"
#include "include/stdlibs/xml_etree_ElementTree.h"
#include "include/stdlibs/xml_dom.h"
#include "include/stdlibs/xml_dom_minidom.h"
#include "include/stdlibs/xml_dom_pulldom.h"
#include "include/stdlibs/xml_sax.h"
#include "include/stdlibs/xml_sax_handler.h"
#include "include/stdlibs/xml_sax_saxutils.h"
#include "include/stdlibs/xml_sax_xmlreader.h"
#include "include/stdlibs/xml_parsers_expat.h"
#include "include/stdlibs/webbrowser.h"
#include "include/stdlibs/wsgiref.h"
#include "include/stdlibs/urllib.h"
#include "include/stdlibs/urllib_request.h"
#include "include/stdlibs/urllib_response.h"
#include "include/stdlibs/urllib_parse.h"
#include "include/stdlibs/urllib_error.h"
#include "include/stdlibs/urllib_robotparser.h"
#include "include/stdlibs/http.h"
#include "include/stdlibs/http_client.h"
#include "include/stdlibs/ftplib.h"
#include "include/stdlibs/poplib.h"
#include "include/stdlibs/imaplib.h"
#include "include/stdlibs/smtplib.h"
#include "include/stdlibs/uuid.h"
#include "include/stdlibs/socketserver.h"
#include "include/stdlibs/http_server.h"
#include "include/stdlibs/http_cookies.h"
#include "include/stdlibs/http_cookiejar.h"
#include "include/stdlibs/xmlrpc.h"
#include "include/stdlibs/xmlrpc_client.h"
#include "include/stdlibs/xmlrpc_server.h"
#include "include/stdlibs/ipaddress.h"
#include "include/stdlibs/wave.h"
#include "include/stdlibs/colorsys.h"
#include "include/stdlibs/gettext.h"
#include "include/stdlibs/locale.h"
#include "include/stdlibs/turtle.h"
#include "include/stdlibs/cmd.h"
#include "include/stdlibs/shlex.h"
#include "include/stdlibs/tkinter.h"
#include "include/stdlibs/tkinter_colorchooser.h"
#include "include/stdlibs/tkinter_font.h"
#include "include/stdlibs/tkinter_messagebox.h"
#include "include/stdlibs/tkinter_scrolledtext.h"
#include "include/stdlibs/tkinter_dnd.h"
#include "include/stdlibs/tkinter_ttk.h"
#include "include/stdlibs/idle.h"
#include "include/stdlibs/typing.h"
#include "include/stdlibs/pydoc.h"
#include "include/stdlibs/doctest.h"
#include "include/stdlibs/unittest.h"
#include "include/stdlibs/unittest_mock.h"
#include "include/stdlibs/test.h"
#include "include/stdlibs/test_support.h"
#include "include/stdlibs/test_support_socket_helper.h"
#include "include/stdlibs/test_support_script_helper.h"
#include "include/stdlibs/test_support_bytecode_helper.h"
#include "include/stdlibs/test_support_threading_helper.h"
#include "include/stdlibs/test_support_os_helper.h"
#include "include/stdlibs/test_support_import_helper.h"
#include "include/stdlibs/test_support_warnings_helper.h"
#include "include/stdlibs/bdb.h"
#include "include/stdlibs/faulthandler.h"
#include "include/stdlibs/pdb.h"
#include "include/stdlibs/timeit.h"
#include "include/stdlibs/trace.h"
#include "include/stdlibs/tracemalloc.h"
#include "include/stdlibs/ensurepip.h"
#include "include/stdlibs/venv.h"
#include "include/stdlibs/zipapp.h"
#include "include/stdlibs/sys.h"
#include "include/stdlibs/sys_monitoring.h"
#include "include/stdlibs/sysconfig.h"
#include "include/stdlibs/__main__.h"
#include "include/stdlibs/warnings.h"
#include "include/stdlibs/dataclasses.h"
#include "include/stdlibs/contextlib.h"
#include "include/stdlibs/abc.h"
#include "include/stdlibs/atexit.h"
#include "include/stdlibs/traceback.h"
#include "include/stdlibs/__future__.h"
#include "include/stdlibs/gc.h"
#include "include/stdlibs/inspect.h"
#include "include/stdlibs/site.h"
#include "include/stdlibs/code.h"
#include "include/stdlibs/codeop.h"
#include "include/stdlibs/zipimport.h"
#include "include/stdlibs/pkgutil.h"
#include "include/stdlibs/modulefinder.h"
#include "include/stdlibs/runpy.h"
#include "include/stdlibs/importlib.h"
#include "include/stdlibs/importlib_resources.h"
#include "include/stdlibs/importlib_resources_abc.h"
#include "include/stdlibs/importlib_metadata.h"
#include "include/stdlibs/ast.h"
#include "include/stdlibs/symtable.h"
#include "include/stdlibs/token.h"
#include "include/stdlibs/keyword.h"
#include "include/stdlibs/tokenize.h"
#include "include/stdlibs/tabnanny.h"
#include "include/stdlibs/pyclbr.h"
#include "include/stdlibs/py_compile.h"
#include "include/stdlibs/compileall.h"
#include "include/stdlibs/dis.h"
#include "include/stdlibs/pickletools.h"
#include "include/stdlibs/msvcrt.h"
#include "include/stdlibs/winreg.h"
#include "include/stdlibs/winsound.h"
#include "include/stdlibs/posix.h"
#include "include/stdlibs/pwd.h"
#include "include/stdlibs/grp.h"
#include "include/stdlibs/termios.h"
#include "include/stdlibs/tty.h"
#include "include/stdlibs/pty.h"
#include "include/stdlibs/fcntl.h"
#include "include/stdlibs/resource.h"
#include "include/stdlibs/syslog.h"
#include "include/stdlibs/getopt.h"
#include "include/stdlibs/collection_set.h"

#include "include/stdlibs/math.h"
#include "include/stdlibs/random.h"
#include "include/stdlibs/time.h"
#include "include/stdlibs/urllib.h"
#include "include/stdlibs/io.h"
#include "include/stdlibs/file.h"
#include "include/stdlibs/network.h"
#include "include/stdlibs/ktui.h"

// Register all built-in modules
void registerAllModules() {
    pylite::stdlibs::registerBuiltinsModule();
    pylite::stdlibs::registerStringModule();
    pylite::stdlibs::registerReModule();
    pylite::stdlibs::registerDifflibModule();
    pylite::stdlibs::registerTextwrapModule();
    pylite::stdlibs::registerUnicodedataModule();
    pylite::stdlibs::registerStringprepModule();
    pylite::stdlibs::registerReadlineModule();
    pylite::stdlibs::registerRlcompleterModule();
    pylite::stdlibs::registerStructModule();
    pylite::stdlibs::registerCodecsModule();
    pylite::stdlibs::registerDatetimeModule();
    pylite::stdlibs::registerZoneinfoModule();
    pylite::stdlibs::registerCalendarModule();
    pylite::stdlibs::registerCollectionsModule();
    pylite::stdlibs::registerCollectionsAbcModule();
    pylite::stdlibs::registerHeapqModule();
    pylite::stdlibs::registerBisectModule();
    pylite::stdlibs::registerArrayModule();
    pylite::stdlibs::registerWeakrefModule();
    pylite::stdlibs::registerTypesModule();
    pylite::stdlibs::registerCopyModule();
    pylite::stdlibs::registerPprintModule();
    pylite::stdlibs::registerReprlibModule();
    pylite::stdlibs::registerEnumModule();
    pylite::stdlibs::registerGraphlibModule();
    pylite::stdlibs::registerNumbersModule();
    pylite::stdlibs::registerMathModule();
    pylite::stdlibs::registerCmathModule();
    pylite::stdlibs::registerDecimalModule();
    pylite::stdlibs::registerFractionsModule();
    pylite::stdlibs::registerRandomModule();
    pylite::stdlibs::registerStatisticsModule();
    pylite::stdlibs::registerItertoolsModule();
    pylite::stdlibs::registerFunctoolsModule();
    pylite::stdlibs::registerOperatorModule();
    pylite::stdlibs::registerPathlibModule();
    pylite::stdlibs::registerOsPathModule();
    pylite::stdlibs::registerStatModule();
    pylite::stdlibs::registerFilecmpModule();
    pylite::stdlibs::registerTempfileModule();
    pylite::stdlibs::registerGlobModule();
    pylite::stdlibs::registerFnmatchModule();
    pylite::stdlibs::registerLinecacheModule();
    pylite::stdlibs::registerShutilModule();
    pylite::stdlibs::registerPickleModule();
    pylite::stdlibs::registerCopyregModule();
    pylite::stdlibs::registerShelveModule();
    pylite::stdlibs::registerMarshalModule();
    pylite::stdlibs::registerDbmModule();
    pylite::stdlibs::registerSqlite3Module();
    pylite::stdlibs::registerZlibModule();
    pylite::stdlibs::registerGzipModule();
    pylite::stdlibs::registerBz2Module();
    pylite::stdlibs::registerLzmaModule();
    pylite::stdlibs::registerZipfileModule();
    pylite::stdlibs::registerTarfileModule();
    pylite::stdlibs::registerCsvModule();
    pylite::stdlibs::registerConfigparserModule();
    pylite::stdlibs::registerTomllibModule();
    pylite::stdlibs::registerNetrcModule();
    pylite::stdlibs::registerPlistlibModule();
    pylite::stdlibs::registerHashlibModule();
    pylite::stdlibs::registerHmacModule();
    pylite::stdlibs::registerSecretsModule();
    pylite::stdlibs::registerOsModule();
    pylite::stdlibs::registerIoModule();
    pylite::stdlibs::registerTimeModule();
    pylite::stdlibs::registerLoggingModule();
    pylite::stdlibs::registerLoggingConfigModule();
    pylite::stdlibs::registerLoggingHandlersModule();
    pylite::stdlibs::registerPlatformModule();
    pylite::stdlibs::registerErrnoModule();
    pylite::stdlibs::registerCtypesModule();
    pylite::stdlibs::registerArgparseModule();
    pylite::stdlibs::registerOptparseModule();
    pylite::stdlibs::registerGetpassModule();
    pylite::stdlibs::registerFileinputModule();
    pylite::stdlibs::registerCursesModule();
    pylite::stdlibs::registerCursesTextpadModule();
    pylite::stdlibs::registerCursesAsciiModule();
    pylite::stdlibs::registerCursesPanelModule();
    pylite::stdlibs::registerThreadingModule();
    pylite::stdlibs::registerMultiprocessingModule();
    pylite::stdlibs::registerMultiprocessingSharedMemoryModule();
    pylite::stdlibs::registerConcurrentFuturesModule();
    pylite::stdlibs::registerSubprocessModule();
    pylite::stdlibs::registerSchedModule();
    pylite::stdlibs::registerQueueModule();
    pylite::stdlibs::registerContextvarsModule();
    pylite::stdlibs::registerThreadModule();
    pylite::stdlibs::registerAsyncioModule();
    pylite::stdlibs::registerSocketModule();
    pylite::stdlibs::registerSslModule();
    pylite::stdlibs::registerSelectModule();
    pylite::stdlibs::registerSelectorsModule();
    pylite::stdlibs::registerSignalModule();
    pylite::stdlibs::registerMmapModule();
    pylite::stdlibs::registerEmailModule();
    pylite::stdlibs::registerJsonModule();
    pylite::stdlibs::registerMailboxModule();
    pylite::stdlibs::registerMimetypesModule();
    pylite::stdlibs::registerBase64Module();
    pylite::stdlibs::registerBinasciiModule();
    pylite::stdlibs::registerQuopriModule();
    pylite::stdlibs::registerHtmlModule();
    pylite::stdlibs::registerHtmlParserModule();
    pylite::stdlibs::registerHtmlEntitiesModule();
    pylite::stdlibs::registerXmlEtreeElementtreeModule();
    pylite::stdlibs::registerXmlDomModule();
    pylite::stdlibs::registerXmlDomMinidomModule();
    pylite::stdlibs::registerXmlDomPulldomModule();
    pylite::stdlibs::registerXmlSaxModule();
    pylite::stdlibs::registerXmlSaxHandlerModule();
    pylite::stdlibs::registerXmlSaxSaxutilsModule();
    pylite::stdlibs::registerXmlSaxXmlreaderModule();
    pylite::stdlibs::registerXmlParsersExpatModule();
    pylite::stdlibs::registerWebbrowserModule();
    pylite::stdlibs::registerWsgirefModule();
    pylite::stdlibs::registerURLLibModule();
    pylite::stdlibs::registerUrllibRequestModule();
    pylite::stdlibs::registerUrllibResponseModule();
    pylite::stdlibs::registerUrllibParseModule();
    pylite::stdlibs::registerUrllibErrorModule();
    pylite::stdlibs::registerUrllibRobotparserModule();
    pylite::stdlibs::registerHttpModule();
    pylite::stdlibs::registerHttpClientModule();
    pylite::stdlibs::registerFtplibModule();
    pylite::stdlibs::registerPoplibModule();
    pylite::stdlibs::registerImaplibModule();
    pylite::stdlibs::registerSmtplibModule();
    pylite::stdlibs::registerUuidModule();
    pylite::stdlibs::registerSocketserverModule();
    pylite::stdlibs::registerHttpServerModule();
    pylite::stdlibs::registerHttpCookiesModule();
    pylite::stdlibs::registerHttpCookiejarModule();
    pylite::stdlibs::registerXmlrpcModule();
    pylite::stdlibs::registerXmlrpcClientModule();
    pylite::stdlibs::registerXmlrpcServerModule();
    pylite::stdlibs::registerIpaddressModule();
    pylite::stdlibs::registerWaveModule();
    pylite::stdlibs::registerColorsysModule();
    pylite::stdlibs::registerGettextModule();
    pylite::stdlibs::registerLocaleModule();
    pylite::stdlibs::registerTurtleModule();
    pylite::stdlibs::registerCmdModule();
    pylite::stdlibs::registerShlexModule();
    pylite::stdlibs::registerTkinterModule();
    pylite::stdlibs::registerTkinterColorchooserModule();
    pylite::stdlibs::registerTkinterFontModule();
    pylite::stdlibs::registerTkinterMessageboxModule();
    pylite::stdlibs::registerTkinterScrolledtextModule();
    pylite::stdlibs::registerTkinterDndModule();
    pylite::stdlibs::registerTkinterTtkModule();
    pylite::stdlibs::registerIdleModule();
    pylite::stdlibs::registerTypingModule();
    pylite::stdlibs::registerPydocModule();
    pylite::stdlibs::registerDoctestModule();
    pylite::stdlibs::registerUnittestModule();
    pylite::stdlibs::registerUnittestMockModule();
    pylite::stdlibs::registerTestModule();
    pylite::stdlibs::registerTestSupportModule();
    pylite::stdlibs::registerTestSupportSocketHelperModule();
    pylite::stdlibs::registerTestSupportScriptHelperModule();
    pylite::stdlibs::registerTestSupportBytecodeHelperModule();
    pylite::stdlibs::registerTestSupportThreadingHelperModule();
    pylite::stdlibs::registerTestSupportOsHelperModule();
    pylite::stdlibs::registerTestSupportImportHelperModule();
    pylite::stdlibs::registerTestSupportWarningsHelperModule();
    pylite::stdlibs::registerBdbModule();
    pylite::stdlibs::registerFaulthandlerModule();
    pylite::stdlibs::registerPdbModule();
    pylite::stdlibs::registerTimeitModule();
    pylite::stdlibs::registerTraceModule();
    pylite::stdlibs::registerTracemallocModule();
    pylite::stdlibs::registerEnsurepipModule();
    pylite::stdlibs::registerVenvModule();
    pylite::stdlibs::registerZipappModule();
    pylite::stdlibs::registerSysModule();
    pylite::stdlibs::registerSysMonitoringModule();
    pylite::stdlibs::registerSysconfigModule();
    pylite::stdlibs::registerMainModule();
    pylite::stdlibs::registerWarningsModule();
    pylite::stdlibs::registerDataclassesModule();
    pylite::stdlibs::registerContextlibModule();
    pylite::stdlibs::registerAbcModule();
    pylite::stdlibs::registerAtexitModule();
    pylite::stdlibs::registerTracebackModule();
    pylite::stdlibs::registerFutureModule();
    pylite::stdlibs::registerGcModule();
    pylite::stdlibs::registerInspectModule();
    pylite::stdlibs::registerSiteModule();
    pylite::stdlibs::registerCodeModule();
    pylite::stdlibs::registerCodeopModule();
    pylite::stdlibs::registerZipimportModule();
    pylite::stdlibs::registerPkgutilModule();
    pylite::stdlibs::registerModulefinderModule();
    pylite::stdlibs::registerRunpyModule();
    pylite::stdlibs::registerImportlibModule();
    pylite::stdlibs::registerImportlibResourcesModule();
    pylite::stdlibs::registerImportlibResourcesAbcModule();
    pylite::stdlibs::registerImportlibMetadataModule();
    pylite::stdlibs::registerAstModule();
    pylite::stdlibs::registerSymtableModule();
    pylite::stdlibs::registerTokenModule();
    pylite::stdlibs::registerKeywordModule();
    pylite::stdlibs::registerTokenizeModule();
    pylite::stdlibs::registerTabnannyModule();
    pylite::stdlibs::registerPyclbrModule();
    pylite::stdlibs::registerPyCompileModule();
    pylite::stdlibs::registerCompileallModule();
    pylite::stdlibs::registerDisModule();
    pylite::stdlibs::registerPickletoolsModule();
    pylite::stdlibs::registerMsvcrtModule();
    pylite::stdlibs::registerWinregModule();
    pylite::stdlibs::registerWinsoundModule();
    pylite::stdlibs::registerPosixModule();
    pylite::stdlibs::registerPwdModule();
    pylite::stdlibs::registerGrpModule();
    pylite::stdlibs::registerTermiosModule();
    pylite::stdlibs::registerTtyModule();
    pylite::stdlibs::registerPtyModule();
    pylite::stdlibs::registerFcntlModule();
    pylite::stdlibs::registerResourceModule();
    pylite::stdlibs::registerSyslogModule();
    pylite::stdlibs::registerGetoptModule();
    pylite::stdlibs::registerCollectionSetModule();
}

// Run the given source code
void run(const std::string& source, pylite::Interpreter& interpreter) {
    // Reset error flags
    pylite::Error::reset();
    
    // Create a lexer and tokenize the source
    pylite::Lexer lexer(source);
    std::vector<pylite::Token> tokens = lexer.scanTokens();
    
    // If there were lexical errors, stop
    if (pylite::Error::hadError) return;
    
    // Parse the tokens into an AST
    pylite::Parser parser(tokens);
    std::vector<pylite::StmtPtr> statements = parser.parse();
    
    // If there were parsing errors, stop
    if (pylite::Error::hadError) return;
    
    // Interpret the AST
    interpreter.interpret(statements);
}

// Run a file
void runFile(const std::string& path, pylite::Interpreter& interpreter) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << path << std::endl;
        exit(74);
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();
    
    run(source, interpreter);
    
    // Exit with error code if there were errors
    if (pylite::Error::hadError) exit(65);
    if (pylite::Error::hadRuntimeError) exit(70);
}

// Run the REPL (interactive mode)
void runPrompt(pylite::Interpreter& interpreter) {
    std::string line;
    
    std::cout << "PyLite " << "0.1.0" << " (C++ Implementation)" << std::endl;
    std::cout << "Type \"exit()\" to exit." << std::endl;
    std::cout << "Special commands:" << std::endl;
    std::cout << "  jit.stats()   - Show JIT compilation statistics" << std::endl;
    
    while (true) {
        std::cout << ">>> ";
        
        if (!std::getline(std::cin, line)) {
            break;
        }
        
        // Exit REPL if user types "exit()"
        if (line == "exit()") {
            break;
        }
        
        // Handle special JIT-related commands directly
        if (line == "jit.enable()" || line == "jit.disable()") {
            std::cout << "JIT compilation is always enabled and cannot be toggled.\n";
            continue;
        } else if (line == "jit.stats()") {
            std::cout << "JIT Statistics:\n";
            interpreter.printJITStats();
            continue;
        }
        
        // Add a newline character at the end for proper parsing
        run(line + "\n", interpreter);
        
        // Reset error flags for REPL
        pylite::Error::reset();
    }
}

void printUsage() {
    std::cout << "Usage: pylite [options] [script]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --help      Display this help message" << std::endl;
    std::cout << "  --debug     Enable debug mode (shows detailed compilation information)" << std::endl;
}

int main(int argc, char* argv[]) {
    // Register all built-in modules
    registerAllModules();
    
    // Create an interpreter
    pylite::Interpreter interpreter;
    // JIT compilation is always enabled by default
    
    // Parse command-line arguments
    bool runScriptMode = false;
    bool debugMode = false;
    std::string scriptFile;
    
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        
        if (arg == "--no-jit") {
            std::cout << "JIT compilation is always enabled and cannot be disabled" << std::endl;
        } else if (arg == "--debug") {
            debugMode = true;
            std::cout << "Debug mode enabled: Showing detailed compilation information" << std::endl;
        } else if (arg == "--help") {
            printUsage();
            return 0;
        } else if (!arg.empty() && arg[0] != '-') {
            // This must be the script file
            runScriptMode = true;
            scriptFile = arg;
        }
    }
    
    // Set debug output flags based on debug mode
    if (debugMode) {
        // This will make the "JIT compiler initialized successfully" message not appear
        pylite::Error::debugMode = true;
    }
    
    if (runScriptMode) {
        // Check if the file has the .pylite extension
        size_t dotPos = scriptFile.find_last_of('.');
        if (dotPos != std::string::npos) {
            std::string extension = scriptFile.substr(dotPos);
            
            if (extension != ".pylite") {
                std::cerr << "Error: File must have .pylite extension" << std::endl;
                return 64;
            }
        } else {
            std::cerr << "Error: File must have .pylite extension" << std::endl;
            return 64;
        }
        
        runFile(scriptFile, interpreter);
    } else if (argc > 1 && argv[1][0] == '-' && !runScriptMode) {
        // Options were provided but no script file
        runPrompt(interpreter);
    } else {
        // Run interactive mode
        runPrompt(interpreter);
    }
    
    return 0;
}
