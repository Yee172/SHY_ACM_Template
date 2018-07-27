namespace __LOCAL_TEST__
{
    namespace __LOCAL_TEST__
    {
        void __LOCAL_TEST__()
        {
            static int __INDEX__ = 0;
            static time_t __START__;
            static time_t __TEMP__;
            static time_t __END__;
            if (__INDEX__)
            {
                __END__ = clock();
                fprintf(stderr,
                        "┏TIME CONSUMED BY STAGE %d: %.12f ms\n"
                        "┗TOTAL TIME UNTIL STAGE %d: %.12f ms\n",
                        __INDEX__,
                        (__END__ - __TEMP__) / (double)CLOCKS_PER_SEC * 1000,
                        __INDEX__,
                        (__END__ - __START__) / (double)CLOCKS_PER_SEC * 1000);
                __TEMP__ = __END__;
                __INDEX__++;
            }
            else
            {
                freopen("../in.txt", "r", stdin);
                freopen("../out.txt", "w", stdout);
                __START__ = __TEMP__ = clock();
                __INDEX__++;
            }
        }
    }

    namespace __DEBUG__
    {
        template <typename A, typename B>
        ostream &operator << (ostream &os, const pair<A, B> &object)
        { return os << "<pair object at " << &object << "> (" << object.first << ", " << object.second << ")"; }

        template <typename A, typename B>
        ostream &operator << (ostream &os, const map<A, B> &object)
        {
            os << "<map object at " << &object << "> {";
            bool f = false;
            for (const auto &each : object)
            {
                if (f) os << ", ";
                f = true;
                os << each.first << ": " << each.second;
            }
            return os << "}" << flush;
        }

        template <typename T>
        ostream &operator << (ostream &os, const list<T> &object)
        {
            os << "<list object at " << &object << "> [";
            bool f = false;
            for (const auto &each : object)
            {
                if (f) os << ", ";
                f = true;
                os << each;
            }
            return os << "]" << flush;
        }

        template <typename T>
        ostream &operator << (ostream &os, const vector<T> &object)
        {
            os << "<vector object at " << &object << "> [";
            bool f = false;
            for (const auto &each : object)
            {
                if (f) os << ", ";
                f = true;
                os << each;
            }
            return os << "]" << flush;
        }

        template <typename T>
        ostream &operator << (ostream &os, const deque<T> &object)
        {
            os << "<deque object at " << &object << "> [";
            bool f = false;
            for (const auto &each : object)
            {
                if (f) os << ", ";
                f = true;
                os << each;
            }
            return os << "]" << flush;
        }

        template <typename T>
        ostream &operator << (ostream &os, const set<T> &object)
        {
            os << "<set object at " << &object << "> {";
            bool f = false;
            for (const auto &each : object)
            {
                if (f) os << ", ";
                f = true;
                os << each;
            }
            return os << "}" << flush;
        }

        template <typename T>
        ostream &operator << (ostream &os, const multiset<T> &object)
        {
            os << "<multiset object at " << &object << "> {";
            bool f = false;
            for (const auto &each : object)
            {
                if (f) os << ", ";
                f = true;
                os << each;
            }
            return os << "}" << flush;
        }

        template <size_t N>
        ostream &operator << (ostream &os, const bitset<N> &object)
        { return os << "<bitset object at " << &object << "> {" << object.to_string() << "}" << endl; }

        template <typename T>
        ostream &operator << (ostream &os, const stack<T> &object)
        {
            os << "<stack object at " << &object << "> {";
            stack<T> copy = object;
            bool f = false;
            while (!copy.empty())
            {
                if (f) os << ", ";
                f = true;
                T each = copy.top();
                os << each;
                copy.pop();
            }
            return os << "}" << flush;
        }

        template <typename T>
        ostream &operator << (ostream &os, const queue<T> &object)
        {
            os << "<queue object at " << &object << "> {";
            queue<T> copy = object;
            bool f = false;
            while (!copy.empty())
            {
                if (f) os << ", ";
                f = true;
                T each = copy.front();
                os << each;
                copy.pop();
            }
            return os << "}" << flush;
        }

        template <typename T>
        ostream &operator << (ostream &os, const priority_queue<T> &object)
        {
            os << "<priority_queue object at " << &object << "> {";
            priority_queue<T> copy = object;
            bool f = false;
            while (!copy.empty())
            {
                if (f) os << ", ";
                f = true;
                T each = copy.top();
                os << each;
                copy.pop();
            }
            return os << "}" << flush;
        }

        template <typename T>
        ostream &operator << (ostream &os, const priority_queue<T, vector<T>, greater<T> > &object)
        {
            os << "<priority_queue object at " << &object << "> {";
            priority_queue<T, vector<T>, greater<T> > copy = object;
            bool f = false;
            while (!copy.empty())
            {
                if (f) os << ", ";
                f = true;
                T each = copy.top();
                os << each;
                copy.pop();
            }
            return os << "}" << flush;
        }

        void __DEBUG__() { cerr << endl; }

        template<typename H, typename...T>
        void __DEBUG__(const H &head, const T &...tail)
        {
            cerr << head;
            if (sizeof ...(tail)) cerr << ", ";
            __DEBUG__(tail...);
        }
    }
}

#define _______ __LOCAL_TEST__::__LOCAL_TEST__::__LOCAL_TEST__();
#define _debug(...) __LOCAL_TEST__::__DEBUG__::__DEBUG__(__VA_ARGS__);
