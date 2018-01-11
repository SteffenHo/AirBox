var ClosureCompiler = require('google-closure-compiler').compiler;

console.log(ClosureCompiler.COMPILER_PATH); // absolute path the compiler jar
console.log(ClosureCompiler.CONTRIB_PATH); // absolute path the contrib folder which contains

var closureCompiler = new ClosureCompiler([
    '--js', 'src/*.js',
    '--js', 'src/**/*.js',
    '--compilation_level', 'ADVANCED',
    '--js_output_file', 'src/bundle.js',
    '--language_in', 'ECMASCRIPT6',
    '--language_out', 'ECMASCRIPT6',
    '--inject_libraries', 'false',
    '--process_common_js_modules', 'true',
    '--debug'
]);

var compilerProcess = closureCompiler.run(function(exitCode, stdOut, stdErr) {
    //compilation complete
    console.log(exitCode, stdOut, stdErr);

    console.log('compilation complete');
});