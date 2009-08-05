class Core;

class App : public wxApp
{
public:
    //Constructor/Destructor
    App();
    ~App();

    virtual bool OnInit();

private:
    Core* C;
};

