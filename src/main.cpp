#include <iostream>

#include <lead/scene.h>
#include <lead/parser.h>
#include <lead/render.h>
#include <lead/filesystem.h>

int main(int argc, char* argv[]){
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    try{
        Lead::FileResolver resolver(argv[1]);
        Lead::Parser parser;
        Lead::Scene* scene = parser.parseFile(Lead::FileResolver::getSceneFilepath());
        std::cout << scene->toString() <<std::endl;
        Lead::Renderer renderer(scene);

        renderer.render(Lead::FileResolver::getOutputFilepath());
    } catch (Lead::LeadException e) {
        std::cout << e.what() << std::endl;
        std::cout << tfm::format("Ended run!\n");
    }

    return 0;
}

