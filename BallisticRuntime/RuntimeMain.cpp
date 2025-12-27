#include <Ballistic.h>
#include <Entry/Entrypoint.h>

namespace ballistic
{
    class RuntimeApplication : public IApplication
    {
    public:
        bool Init() override {
            std::cout << "Runtime initialized\n";
            return true;
        }

        void Update(float deltaTime) override {}

        void Shutdown() override {
            std::cout << "Runtime shutdown\n";
        }
    };

    Root* CreateRoot() {
        Root* root = new Root();
        root->SetApplication(std::make_unique<RuntimeApplication>());
        return root;
    }
    
} // namespace ballistic

int main(int argc, char** argv) {
    return ballistic::Main(argc, argv);
}
