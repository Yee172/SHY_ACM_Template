namespace __LOCAL_TEST__
{
    map<int, string> __CHAR_TABLE__;
    bool __SHOW_TYPE_SWITCH__ = false;
    bool __SHOW_TYPE_BY_ID_SWITCH__ = true;
    bool __SHOW_ADDRESS_SWITCH__ = false;

    class LOCAL_TEST
    {
    private:
        int __INDEX__ = 0;
        int __INDEX_WIDTH__ = 2;
        time_t __START__;
        time_t __TEMP__;
        time_t __END__ = 0;

        inline void __INITIALIZE_TABLE__()
        {
            __CHAR_TABLE__[0] = "\\0", __CHAR_TABLE__[7] = "\\a";
            __CHAR_TABLE__[8] = "\\b", __CHAR_TABLE__[9] = "\\t";
            __CHAR_TABLE__[10] = "\\n", __CHAR_TABLE__[11] = "\\v";
            __CHAR_TABLE__[12] = "\\f", __CHAR_TABLE__[13] = "\\r";
        }

    public:
        LOCAL_TEST()
        {
            freopen("../in.txt", "r", stdin);
            freopen("../out.txt", "w", stdout);
            __START__ = __TEMP__ = clock();
            __INDEX__++;

            __INITIALIZE_TABLE__();
        }

        void __LOCAL_TEST__()
        {
            __END__ = clock();
            cerr << fixed << setprecision(12)
                 << "┏TIME CONSUMED BY STAGE " << setw(__INDEX_WIDTH__) << __INDEX__ << ": "
                 << (__END__ - __TEMP__) / (double)CLOCKS_PER_SEC * 1000 << " ms" << endl
                 << "┗TOTAL TIME UNTIL STAGE " << setw(__INDEX_WIDTH__) << __INDEX__ << ": "
                 << (__END__ - __START__) / (double)CLOCKS_PER_SEC * 1000 << " ms" << endl;
            __TEMP__ = __END__;
            __INDEX__++;
        }

        ~LOCAL_TEST() { __LOCAL_TEST__(); }
    }__LOCAL_TEST__;

    namespace __DEBUG__
    {
        using std::to_string;

        string to_string(const char object)
        {
            ostringstream os;
            __CHAR_TABLE__[object].empty() ? os << "'" << object << "'" : os << "'" << __CHAR_TABLE__[object] << "'";
            return os.str();
        }

        string to_string(const char * object)
        {
            ostringstream os;
            os << '"' << object << '"';
            return os.str();
        }

#define __TEMPLATE_TYPE_SINGLE__(TYPE) \
        TYPE<T##EMPLATE>

#define __TEMPLATE_TYPE_PAIR__(TYPE) \
        TYPE<TEMPLATE1, T##EMPLATE2>

#define __HEAD_TO_STRING__(TYPE) \
        ostringstream os;\
        if (__SHOW_TYPE_SWITCH__ or __SHOW_ADDRESS_SWITCH__)\
        {\
            os << "<";\
            if (__SHOW_TYPE_SWITCH__) os << #TYPE << " object";\
            if (__SHOW_TYPE_SWITCH__ and __SHOW_ADDRESS_SWITCH__) os << " at ";\
            if (__SHOW_ADDRESS_SWITCH__) os << &object;\
            os << "> ";\
        }

#define __ITERATOR_TRAVERSAL_SINGLE__ \
        bool f = false;\
        for (const auto &each : object)\
        {\
            if (f) os << ", ";\
            f = true;\
            os << to_string(each);\
        }

#define __ITERATOR_TRAVERSAL_PAIR__ \
        bool f = false;\
        for (const auto &each : object)\
        {\
            if (f) os << ", ";\
            f = true;\
            os << to_string(each.first) << ": " << to_string(each.second);\
        }

#define __POP_TRAVERSAL__(OPERATOR) \
        bool f = false;\
        while (!copy.empty())\
        {\
            if (f) os << ", ";\
            f = true;\
            os << to_string(cop##y.OPERATOR());\
            copy.pop();\
        }

#define __ITERATOR_BRACE_PAIR__(TYPE) \
        template <typename TEMPLATE1, typename TEMPLATE2>\
        string to_string(const __TEMPLATE_TYPE_PAIR__(TYPE) &object)\
        {\
            __HEAD_TO_STRING__(TYPE)\
            os << "{";\
            __ITERATOR_TRAVERSAL_PAIR__\
            os << "}";\
            return os.str();\
        }

#define __ITERATOR_SQUARE_BRACKET_SINGLE__(TYPE) \
        template <typename TEMPLATE>\
        string to_string(const __TEMPLATE_TYPE_SINGLE__(TYPE) &object)\
        {\
            __HEAD_TO_STRING__(TYPE)\
            os << "[";\
            __ITERATOR_TRAVERSAL_SINGLE__\
            os << "]";\
            return os.str();\
        }

#define __ITERATOR_BRACE_SINGLE__(TYPE) \
        template <typename TEMPLATE>\
        string to_string(const __TEMPLATE_TYPE_SINGLE__(TYPE) &object)\
        {\
            __HEAD_TO_STRING__(TYPE)\
            os << "{";\
            __ITERATOR_TRAVERSAL_SINGLE__\
            os << "}";\
            return os.str();\
        }

#define __POP_BRACE__(TYPE, OPERATOR) \
        template <typename TEMPLATE>\
        string to_string(const __TEMPLATE_TYPE_SINGLE__(TYPE) &object)\
        {\
            __HEAD_TO_STRING__(TYPE)\
            os << "{";\
            __TEMPLATE_TYPE_SINGLE__(TYPE) copy = object;\
            __POP_TRAVERSAL__(OPERATOR)\
            os << "}";\
            return os.str();\
        }

        template <typename A, typename B>
        string to_string(const pair<A, B> &object)
        {
            __HEAD_TO_STRING__(pair)
            os << "(" << to_string(object.first) << ", " << to_string(object.second) << ")";
            return os.str();
        }

        template <size_t N>
        string to_string(const bitset<N> &object)
        {
            __HEAD_TO_STRING__(bitset)
            os << "{" << object.to_string() << "}";
            return os.str();
        }

        __ITERATOR_BRACE_PAIR__(map)
        __ITERATOR_BRACE_PAIR__(multimap)
        __ITERATOR_SQUARE_BRACKET_SINGLE__(list)
        __ITERATOR_SQUARE_BRACKET_SINGLE__(vector)
        __ITERATOR_SQUARE_BRACKET_SINGLE__(deque)
        __ITERATOR_BRACE_SINGLE__(set)
        __ITERATOR_BRACE_SINGLE__(multiset)
        __POP_BRACE__(stack, top)
        __POP_BRACE__(queue, front)
        __POP_BRACE__(priority_queue, top)

        template <typename TEMPLATE>
        string to_string(const priority_queue<TEMPLATE, vector<TEMPLATE>, greater<TEMPLATE> > &object)
        {
            __HEAD_TO_STRING__(priority_queue)
            os << "{";
            priority_queue<TEMPLATE, vector<TEMPLATE>, greater<TEMPLATE> > copy = object;
            __POP_TRAVERSAL__(top)
            os << "}";
            return os.str();
        }

        queue<vector<char> > VARIABLE;
        void __INITIALIZE_VARIABLES__(const char * va_args)
        {
            while (!VARIABLE.empty()) VARIABLE.pop();
            int length = static_cast<int>(strlen(va_args));
            int bracket_count = 0;
            vector<char> var(0);
            for (int i = 0; i < length; i++)
            {
                if (va_args[i] == '(' || va_args[i] == '[' || va_args[i] == '{') bracket_count++;
                if (va_args[i] == ')' || va_args[i] == ']' || va_args[i] == '}') bracket_count--;
                if (va_args[i] == ',' && bracket_count == 0)
                {
                    while (var.back() == ' ') var.pop_back();
                    VARIABLE.push(var);
                    var.resize(0);
                }
                else if (va_args[i] == ' ' && var.size() == 0) continue;
                else var.push_back(va_args[i]);
            }
            while (!var.empty() && var.back() == ' ') var.pop_back();
            VARIABLE.push(var);
            var.resize(0);
        }

        char show_variable_name()
        {
            if (!VARIABLE.empty())
            {
                for (auto c : VARIABLE.front()) cerr << c;
                VARIABLE.pop();
            }
            return ' ';
        }

        void __DEBUG__() { cerr << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m" << endl; }

        template <typename H, typename ...T>
        void __DEBUG__(const H &head, const T &...tail)
        {
            cerr << "┃ " << show_variable_name() << ": " << to_string(head) << endl;
            __DEBUG__(tail...);
        }

        void __SHOW_BASIC_INFO__(const char * function, const int line)
        {
            cerr << "\033[94m┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl <<
                            "┃ DEBUG in function '" << function << "' at line " << line << ":" << endl;
        }
#undef __TEMPLATE_TYPE_SINGLE__
#undef __TEMPLATE_TYPE_PAIR__
#undef __HEAD_TO_STRING__
#undef __ITERATOR_TRAVERSAL_SINGLE__
#undef __ITERATOR_TRAVERSAL_PAIR__
#undef __POP_TRAVERSAL__
#undef __ITERATOR_BRACE_PAIR__
#undef __ITERATOR_SQUARE_BRACKET_SINGLE__
#undef __ITERATOR_BRACE_SINGLE__
#undef __POP_BRACE__
    }
}

#define _______ __LOCAL_TEST__::__LOCAL_TEST__.__LOCAL_TEST__();
#define _debug(...) __LOCAL_TEST__::__DEBUG__::__SHOW_BASIC_INFO__(__FUNCTION__, __LINE__), \
                    __LOCAL_TEST__::__DEBUG__::__INITIALIZE_VARIABLES__(#__VA_ARGS__), \
                    __LOCAL_TEST__::__DEBUG__::__DEBUG__(__VA_ARGS__);
