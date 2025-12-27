#include <Ballistic.h>
#include <Entry/Entrypoint.h>

namespace ballistic
{
    class RuntimeApplication : public IApplication
    {
    public:
        bool Init() override {
            std::cout << "Runtime initialized\n";

            m_window = std::make_unique<Window>();
            if (!m_window->Init()) {
                return false;
            }

            return true;
        }

        void Update(float deltaTime) override {
            m_window->Update();

            if (m_window->ShouldClose())
                Root::getSingleton().RequestShutdown();
        }

        void Shutdown() override {
            m_window->Shutdown();

            std::cout << "Runtime shutdown\n";
        }

    private:
        std::unique_ptr<Window> m_window;
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
