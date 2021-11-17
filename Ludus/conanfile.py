from conans import ConanFile
#from parktoma.vscconan import update_cpp_tools

class BasicTestConan(ConanFile):
    requires = "fmt/[>5.3.0]", "opengl/system", "glad/0.1.34", "glfw/3.3.5", "glm/0.9.9.8"
    generators = "visual_studio"

    #def imports(self):
    #    update_cpp_tools(self, conanfile_path=__file__)
