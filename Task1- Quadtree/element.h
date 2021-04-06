#include <string>

namespace colour{
    class element{
        protected:
            string status;

        public:
            virtual void setStatus(string status) = 0;
            virtual string getStatus() const = 0;

            virtual void validate(string s) = 0;
            virtual void print() = 0;
    };
}