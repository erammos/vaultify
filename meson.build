project(
  'vaultify',
  'c',
  version: '0.1',
  default_options: ['warning_level=3', 'c_std=gnu2x'],
)

openslldeps = dependency('openssl')
sqlite = dependency('sqlite3')
raylib = dependency('raylib')
unity_subproject = subproject('Unity')
unity_dependency = unity_subproject.get_variable('unity_dep')
unity_gen_runner = unity_subproject.get_variable('gen_test_runner')

src = files(
  'src' / 'entry.c',
  'src' / 'vaultify.c',
  'src' / 'encryption.c',
  'src' / 'entries.c',
)

test1 = files(
  'test' / 'test_encryption.c',
  )
  test2 = files(
  'test' / 'test_entries.c',
  )
inc = include_directories('src')

executable(
  'vaultify',
  [src, 'src' / 'main.c'],
  dependencies: [sqlite,raylib, openslldeps],
  c_args: '-DVLT_COMPILATION',
  include_directories: inc,
  install: true,
)

test1 = executable(
  'test1',
  [src, test1, unity_gen_runner.process( 'test' / 'test_encryption.c')],
  dependencies: [openslldeps, unity_dependency],
  c_args: '-DVLT_COMPILATION',
  include_directories: inc,
)
test2 = executable(
  'test2',
  [src, test2, unity_gen_runner.process( 'test' / 'test_entries.c')],
  dependencies: [openslldeps,unity_dependency],
  c_args: '-DVLT_COMPILATION',
  include_directories: inc,
)
test('test1',test1)
test('test2',test2)