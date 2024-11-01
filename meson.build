project(
    'braindance',
    'c',
    version : '0.0.0',
    meson_version : '>=1.5',
    license : 'Mozilla Public License Version 2.0',
    license_files : 'LICENSE',
    default_options : [
        'c_std=c2x',
    ],
)

src_headers = include_directories('include')

executable(
    meson.project_name(),
    run_command('find', 'src', '-depth', '-type', 'f', check : true).stdout().strip().split('\n'),
    install : true,
    native : true,
    include_directories : src_headers,
)

lib = shared_library(
    meson.project_name() + 'lib',
    run_command('find', 'src', '-depth', '-type', 'f', '-not', '-name', 'main.c', check : true).stdout().strip().split('\n'),
    include_directories : src_headers,
)

foreach test_file : run_command('find', 'test', '-depth', '-type', 'f', check : true).stdout().strip().split('\n')
    test_name = test_file.split('/')[-1].substring(0, -2)
    test_exe = executable(
        test_name,
        test_file,
        link_with : lib,
        build_by_default : false,
        d_unittest : true,
        include_directories : src_headers
    )
    test(test_name, test_exe)
endforeach
