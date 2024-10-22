project(
    'braindance',
    'c',
    version : '0.0.0',
    default_options : [
        'c_std=c2x',
        'warning_level=3'
    ],
    license : '',
)

compiler = meson.get_compiler('c')

src = run_command('find', 'src', '-depth', '-type', 'f', check : true).stdout().strip().split('\n')


build_args = [
    '-O3',
    '-DNAME=' + meson.project_name(),
    '-DVERSION=' + meson.project_version(),
]

header = include_directories('include')

executable(
    meson.project_name(),
    sources : src,
    install : true,
    c_args : build_args,
    include_directories : header
)