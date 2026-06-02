#include <QApplication> // Bibliotecă obligatorie Qt
#include <iostream>
#include "Repository.h"
#include "RepositoryFactory.h"
#include "Controller.h"
#include "UI.h"
#include <string>

#include "Tests.h"

int main(int argc, char *argv[]) {
    Tests::runAllTests();
    // initialize the app
    QApplication a(argc, argv);

    std::string repoType, filename = "";

    std::cout << "What type of repo? (memory/csv/json): ";
    std::getline(std::cin, repoType);

    if (repoType == "csv" || repoType == "json") {
        std::cout << "Filename: ";
        std::getline(std::cin, filename);
    }

    try {
        std::unique_ptr<Repository> repo = RepositoryFactory::create(repoType, filename);

        if (repoType == "memory") {
            repo->add(std::make_shared<CraftItem>(1, "Ceramic Vase", Category::Blank, 45.0, 10));
            repo->add(std::make_shared<CraftItem>(2, "Paintbrush Set", Category::Tool, 25.5, 5));
            repo->add(std::make_shared<CraftItem>(3, "Jute Twine Rope", Category::Material, 12.0, 50));
        }

        Controller controller(*repo);
        UI ui(controller);
        ui.show();

        return a.exec();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
