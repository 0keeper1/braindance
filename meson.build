project(
    'braindance',
    'c',
    version : '0.0.0',
    default_options : [
        'c_std=c2x',
        'warning_level=3',
        'march=native',
    ],
    meson_version : '>=1.5.0'
)

compiler = meson.get_compiler('c')

src = run_command('find', 'src', '-depth', '-type', 'f', check : true).stdout().strip().split('\n')

build_args = [
    '-O3',
    '-DNAME=' + meson.project_name(),
    '-DVERSION=' + meson.project_version(),
]


message(' ', host_machine.cpu_family())

header = include_directories('include')

braindance = executable(
    meson.project_name(),
    sources : src,
    install : true,
    native : true,
    c_args : build_args,
    include_directories : header
)

src_test = run_command('find', 'test', '-depth', '-type', 'f', check : true).stdout().strip().split('\n')

braindance_lib = static_library(
    meson.project_name() + '_lib',
    sources : run_command('find', 'src', '-depth', '-type', 'f', '-not', '-name', 'main.c', check : true).stdout().strip().split('\n'),
    c_args : build_args,
    include_directories : header
)

dep = declare_dependency(
    include_directories : header,
    link_with : braindance_lib
)

braindance_test = executable(
    meson.project_name() + '_test',
    sources : src_test,
    c_args : build_args,
    dependencies : dep
)

test('test', braindance_test)