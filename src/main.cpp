#include <iostream>

#include <lead/scene.h>
#include <lead/parser.h>
#include <lead/render.h>

int main(){
    try{
        Lead::Parser parser;
        Lead::Scene* scene = parser.parseFile("C:/Users/karti/Documents/Programming/PBR/scenes/test.xml");
        std::cout << scene->toString() <<std::endl;
        Lead::Renderer renderer(scene);

        renderer.render("C:/Users/karti/Documents/Programming/PBR/scenes/test.exr");
    } catch (Lead::LeadException e) {
        std::cout << e.what() << std::endl;
        std::cout << tfm::format("Ended run!\n");
    }

    return 0;
}

