#include <cassert>
#include <typeinfo>

int main() {
    //int *
    int *alpha = new int(5);
    assert(typeid(alpha) == typeid(int *));
    
    // int &
    int &beta = *alpha;
    assert(typeid(beta) == typeid(int &));
    
    //double
    double gamma = 5.5;
    assert(typeid(gamma) == typeid(double));
    
    //A *
    struct A {
        int value;
    };
    A *delta = new A{10};
    assert(typeid(delta) == typeid(A *));

    //char const *
    char const *epsilon = "Hello World!";
    assert(typeid(epsilon) == typeid(char const *));

    //char const &
    char const &zeta = *epsilon;
    assert(typeid(zeta) == typeid(char const &));
    
    //long[7]
    long eta[7] = {1, 2, 3, 4, 5, 6, 7};
    assert(typeid(eta) == typeid(long[7]));
    
    //int **
    int **theta = new int*[7];
    assert(typeid(theta) == typeid(int **));
    
    //int *&
    int *&iota = *theta;
    assert(typeid(iota) == typeid(int *&));
    
    //float &
    float *kappa = new float(5.5);
    float &lambda = *kappa;
    assert(typeid(lambda) == typeid(float &));

    //int (*) ()
    int (*mu) () = []() -> int {return 5;};
    assert(typeid(mu) == typeid(int (*) ()));

    //int (*&) ()
    int (*&nu) () = mu;
    assert(typeid(nu) == typeid(int (*&) ()));

    //char *(*) (char *, char *)
    char *(*omnicron) (char *, char *) = [](char *pi, char *rho) -> char * {return pi;};
    assert(typeid(omnicron) == typeid(char *(*) (char *, char *)));

    //int A::*
    int A::*sigma = &A::value;
    assert(typeid(sigma) == typeid(int A::*));

    //int (A::*) (int *)
    class B {
        public:
            int memberFunc(int* yod) {
                return *yod;
            }
    };
    B *b = new B();
    int (B::*tau) (int *) = &B::memberFunc;
    assert(typeid(tau) == typeid(int (B::*) (int *)));

    //int (A::**)(int *)
    int (B::*phi) (int *) = &B::memberFunc;
    int (B::**chi) (int *) = &phi;
    assert(typeid(phi) == typeid(int (B::**) (int *)));

    //int (A::*&)(int *)
    int (B::*psi) (int *) = &B::memberFunc;
    assert(typeid(psi) == typeid(int (B::*&) (int *)));

    //int (A::*)(double (*)(float &))
    class C {
        public:
            int memberFunc(double (*aleph)(float &)) {
                float f = 1.0f;
                return static_cast<int>(aleph(f));
            }
    };
    int (C::*omega) (double (*)(float &)) = &C::memberFunc;
    assert(typeid(omega) == typeid(int (C::*) (double (*)(float &))));

    //void (*p[10]) (void (*)() );
    using gimel = void (*)();
    using beth = void (*)(gimel);
    beth p[10];
   assert(typeid(beth).name() == typeid(void (*)(void (*)())).name());
   assert(typeid(p).name() == typeid(void (*[10])(void (*)())).name());

}