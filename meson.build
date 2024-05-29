project(
  'vaultify',
  'c',
  version: '0.1',
  default_options: ['warning_level=3', 'c_std=gnu2x'],
)

gtkdeps = dependency('gtk+-3.0')
openslldeps = dependency('openssl')

unity_subproject = subproject('Unity')
unity_dependency = unity_subproject.get_variable('unity_dep')
unity_gen_runner = unity_subproject.get_variable('gen_test_runner')

src = files(
  'src' / 'entry.c',
  'src' / 'vaultify.c',
  'src' / 'encryption.c',
)

tests = files('test' / 'test_encryption.c')
inc = include_directories('src')

executable(
  'vaultify',
  [src, 'src' / 'main.c'],
  dependencies: [gtkdeps, openslldeps],
  c_args: '-DVLT_COMPILATION',
  include_directories: inc,
  install: true,
)

test1 = executable(
  'test1',
  [src, tests, unity_gen_runner.process( 'test' / 'test_encryption.c')],
  dependencies: [openslldeps, unity_dependency],
  c_args: '-DVLT_COMPILATION',
  include_directories: inc,
)
test('test1',test1)