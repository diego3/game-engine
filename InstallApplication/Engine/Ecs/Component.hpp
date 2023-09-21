
class Component {
public:
    Component();

    void Init();

    virtual void Update(float elapsedTime) = 0;

    virtual void Draw(void* target);
};