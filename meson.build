project('tiny_manna', 'cpp',
        default_options: [ 'cpp_std=c++14', 'warning_level=2' ]
)

tiny_manna = executable('tiny_manna',
    'tiny_manna.cpp'
)

cpp = meson.get_compiler('cpp')

gl_dep = cpp.find_library('GL', required: false)
glfw_dep = cpp.find_library('glfw', required: false)

demo = executable('demo',
    'tiny_manna.cpp',
    cpp_args: '-DGRAPHICS',
    dependencies: [ glfw_dep, gl_dep ]
)

