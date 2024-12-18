#include <iostream>

#include <lead/common.h>
#include <lead/scene.h>
#include <lead/parser.h>



int main(){
    try{
        Parser parser;
        Scene* scene = parser.parseFile("C:/Users/karti/Documents/Programming/PBR/scenes/test.xml");
    } catch (LeadException e) {
        std::cout << e.what() << std::endl;
        std::cout << tfm::format("Ended run!\n");
    }
}

