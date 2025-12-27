#include <Ballistic.h>
#include <Entry/Entrypoint.h>

namespace ballistic
{
    class EditorApplication : public IApplication
    {
    public:
        bool Init() override {
            std::cout << "Editor initialized\n";
            return true;
        }

        void Update(float deltaTime) override {}

        void Shutdown() override {
            std::cout << "Editor shutdown\n";
        }
    };

    Root* CreateRoot() {
        Root* root = new Root();
        root->SetApplication(std::make_unique<EditorApplication>());
        return root;
    }
    
} // namespace ballistic

int main(int argc, char** argv) {
    return ballistic::Main(argc, argv);
}