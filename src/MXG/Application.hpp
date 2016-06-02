#ifndef MXG_APPLICATION_HPP_
#define MXG_APPLICATION_HPP_

namespace mxg {

class Application {
    public:
        virtual ~Application() {}

        int run();
        void exit();
        void exit(const int errorCode);

    protected:
        virtual void create() {}
        virtual void destroy() {}
        virtual void tick() {}

    private:
        int errorCode_{0};
        bool running_{true};
};

} /* namespace mxg */
#endif /* MXG_APPLICATION_HPP_ */
