//
//  "$Id: FunctionTemplate.h 132341 2013-08-16 02:14:42Z qin_fenglin $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//
// 会在Function.h中包含多次，本头文件不能使用保护宏
#define FUNCTION_FUNCTION DAHUA_JOIN(TFunction,FUNCTION_NUMBER)

/// \class FUNCTION_FUNCTION
/// \brief 函数指针类模块。
///
/// 支持普通函数指针和成员函数指针的保存，比较，调用等操作。对于成员函数，
/// 要求类只能是普通类或者是单继承的类，不能是多继承或虚继承的类。FUNCTION_FUNCTION是一个宏，
/// 根据参数个数会被替换成TFunctionN，用户通过TFunctionN<R, T1, T2, T3,..,TN>方式来使用，
/// R表示返回值类型，TN表示参数类型， N表示函数参数个数，目前最大参数为6。示例如下：
/// \code
/// int g(int x)
/// {
/// 	return x * 2;
/// }
/// class G
/// {
/// public:
/// 	int g(int x)
/// 	{
/// 		return x * 3;
/// 	}
/// }gg;
/// void test()
/// {
/// 	TFunction1<int, int> f1(g);
/// 	TFunction1<int, int> f2(&G::g, &gg);
/// 	assert(f1(1) = 2);
/// 	assert(f2(1) = 3);
/// 	f1 = f2;
/// 	assert(f1 == f2);
/// }
/// \endcode


////////////////////////////////////////////////////////////////////////////////

// Comma if nonzero number of arguments
#if FUNCTION_NUMBER == 0
#  define FUNCTION_COMMA
#else
#  define FUNCTION_COMMA ,
#endif // FUNCTION_NUMBER > 0

#define FUNCTION_INVOKER DAHUA_JOIN(function_invoker, FUNCTION_NUMBER)
#define FUNCTION_VOID_INVOKER DAHUA_JOIN(function_void_invoker, FUNCTION_NUMBER)
#define GET_FUNCTION_INVODER DAHUA_JOIN(get_function_invoker, FUNCTION_NUMBER)
#define MEM_FUNCTION_INVOKER DAHUA_JOIN(mem_function_invoker, FUNCTION_NUMBER)
#define MEM_FUNCTION_VOID_INVOKER DAHUA_JOIN(mem_function_void_invoker, FUNCTION_NUMBER)
#define GET_MEM_FUNCTION_INVODER DAHUA_JOIN(get_mem_function_invoker, FUNCTION_NUMBER)


////////////////////////////////////////////////////////////////////////////////

template<FUNCTION_CLASS_TYPES> struct FUNCTION_INVOKER
{
	template<class F>
	static typename Detail::function_return_type<R>::type invoke(F f FUNCTION_COMMA FUNCTION_TYPE_ARGS)
	{
		return f(FUNCTION_ARGS);
	}
};

template<FUNCTION_CLASS_TYPES> struct FUNCTION_VOID_INVOKER
{
	template<class F>
	static typename Detail::function_return_type<R>::type invoke(F f FUNCTION_COMMA FUNCTION_TYPE_ARGS)
	{
		DAHUA_FUNCTION_RETURN(f(FUNCTION_ARGS));
	}
};

template<class RT> struct GET_FUNCTION_INVODER
{
	template<FUNCTION_CLASS_TYPES> struct Invoker
	{
		typedef FUNCTION_INVOKER<R FUNCTION_COMMA FUNCTION_TYPES> type;
	};
};

template<> struct GET_FUNCTION_INVODER<void>
{
	template<FUNCTION_CLASS_TYPES> struct Invoker
	{
		typedef FUNCTION_VOID_INVOKER<R FUNCTION_COMMA FUNCTION_TYPES> type;
	};
};

////////////////////////////////////////////////////////////////////////////////

template<FUNCTION_CLASS_TYPES> struct MEM_FUNCTION_INVOKER
{
	template<class O, class F>
		static typename Detail::function_return_type<R>::type invoke(O o, F f FUNCTION_COMMA FUNCTION_TYPE_ARGS)
	{
		return (o->*f)(FUNCTION_ARGS);
	}
};

template<FUNCTION_CLASS_TYPES> struct MEM_FUNCTION_VOID_INVOKER
{
	template<class O, class F>
		static typename Detail::function_return_type<R>::type invoke(O o, F f FUNCTION_COMMA FUNCTION_TYPE_ARGS)
	{
		DAHUA_FUNCTION_RETURN((o->*f)(FUNCTION_ARGS));
	}
};

template<class RT> struct GET_MEM_FUNCTION_INVODER
{
	template<FUNCTION_CLASS_TYPES> struct Invoker
	{
		typedef MEM_FUNCTION_INVOKER<R FUNCTION_COMMA FUNCTION_TYPES> type;
	};
};

template<> struct GET_MEM_FUNCTION_INVODER<void>
{
	template<FUNCTION_CLASS_TYPES> struct Invoker
	{
		typedef MEM_FUNCTION_VOID_INVOKER<R FUNCTION_COMMA FUNCTION_TYPES> type;
	};
};

////////////////////////////////////////////////////////////////////////////////


template <FUNCTION_CLASS_TYPES>
class FUNCTION_FUNCTION
{
	class X{};

	typedef R (X::*MEM_FUNCTION)(FUNCTION_TYPES);
	typedef R (*PTR_FUNCTION)(FUNCTION_TYPES);

public:
	enum FunctionType
	{
		typeEmpty,
		typeMember,
		typePointer,
		typeObject,
		typeReuse = 16,
		typeAllReuse = -1,
	};
	union
	{
		struct
		{
			MEM_FUNCTION proc;
			X* obj;
		}memFunction;
		PTR_FUNCTION ptrFunction;
	}m_function;

	FunctionType m_type;
	const char* m_objectType;

public:
	/// 缺省构造函数
	FUNCTION_FUNCTION( )
		:m_type(typeEmpty), m_objectType(0)
	{
	}

	/// 接受成员函数指针构造函数，将类的成员函数和类对象的指针绑定并保存。
	/// \param [in] f 类的成员函数
	/// \param [in] o 类对象的指针
	/// \param [in] reuse 复用id，(uint32_t)-1表示所有id，仅用于从signal中删除所有f和o相同的函数
	template<typename O>
		FUNCTION_FUNCTION(R(O::*f)(FUNCTION_TYPES), const O * o, uint32_t reuse)
	{
		if(reuse < (uint32_t)typeReuse)
		{
			m_type = typeEmpty;
			m_objectType = 0;
			printf("FUNCTION_FUNCTION::FUNCTION_FUNCTION invalid reuse id : %u, typeid : %s\n", reuse, typeid(o).name());
			return;
		}
		m_type = (FunctionType)reuse;
		m_function.memFunction.proc = Detail::horrible_cast<MEM_FUNCTION>(f); //what's safty, hei hei
		m_function.memFunction.obj = Detail::horrible_cast<X*>(o);
		m_objectType = typeid(o).name();
	}

	/// 接受成员函数指针构造函数，将类的成员函数和类对象的指针绑定并保存。
	/// \param [in] f 类的成员函数
	/// \param [in] o 类对象的指针
	template<typename O>
		FUNCTION_FUNCTION(R(O::*f)(FUNCTION_TYPES), const O * o)
	{
		m_type = typeMember;
		m_function.memFunction.proc = Detail::horrible_cast<MEM_FUNCTION>(f); //what's safty, hei hei
		m_function.memFunction.obj = Detail::horrible_cast<X*>(o);
		m_objectType = typeid(o).name();
	}

	/// 接受普通函数指针构造函数，保存普通函数指针。
	/// \param [in] f 函数指针
	FUNCTION_FUNCTION(PTR_FUNCTION f)
	{
		if(f)
		{
			m_type = typePointer;
			m_function.ptrFunction = f;
			m_objectType = 0;
		}
		else
		{
			m_type = typeEmpty;
			m_objectType = 0;
		}
	}

	/// 拷贝构造函数
	/// \param [in] f 源函数指针对象
	FUNCTION_FUNCTION& operator=(const FUNCTION_FUNCTION& f)
	{
		if (&f == this)
			return *this;
		m_function = f.m_function;
		m_type = f.m_type;
		m_objectType = f.m_objectType;
		return *this;
	}

	/// 将类的成员函数和类对象的指针绑定并保存。其他类型的函数指针可以=运算符和隐式转换直接完成。
	template<typename O>
	void bind(R(O::*f)(FUNCTION_TYPES), const O * o)
	{
		*this = FUNCTION_FUNCTION(f, o);
	}

	/// 判断函数指针是否为空
	bool empty() const
	{
		return (m_type == typeEmpty);
	}

	/// 判断函数指针是否表示所有复用函数
	bool allReuse() const
	{
		return (m_type == typeAllReuse);
	}

	/// 比较两个函数指针是否相等
	bool operator==(const FUNCTION_FUNCTION& f) const
	{
		if((uint32_t)m_type >= (uint32_t)typeReuse && (uint32_t)f.m_type >= (uint32_t)typeReuse)
		{
			if(m_type == typeAllReuse || f.m_type == typeAllReuse)
			{
				return (m_function.memFunction.proc == f.m_function.memFunction.proc
					&& m_function.memFunction.obj == f.m_function.memFunction.obj);
			}
			else
			{
				return (m_type == f.m_type
					&& m_function.memFunction.proc == f.m_function.memFunction.proc
					&& m_function.memFunction.obj == f.m_function.memFunction.obj);
			}
		}
		else if(m_type != f.m_type)
		{
			return false;
		}
		if(m_type == typeMember)
		{
			return (m_function.memFunction.proc == f.m_function.memFunction.proc
				&& m_function.memFunction.obj == f.m_function.memFunction.obj);
		}
		else if(m_type == typePointer)
		{
			return (m_function.ptrFunction == f.m_function.ptrFunction);
		}
		else
		{
			return true;
		}
	}

	/// 重载()运算符，可以以函数对象的形式来调用保存的函数指针。
	inline typename Detail::function_return_type<R>::type operator()(FUNCTION_TYPE_ARGS)
	{
		if(m_type == typeMember)
		{
			typedef typename GET_MEM_FUNCTION_INVODER<R>::template Invoker<R FUNCTION_COMMA FUNCTION_TYPES>::type Invoker;
			return Invoker::invoke(m_function.memFunction.obj, m_function.memFunction.proc FUNCTION_COMMA FUNCTION_ARGS);
		}
		else if(m_type == typePointer)
		{
			typedef typename GET_FUNCTION_INVODER<R>::template Invoker<R FUNCTION_COMMA FUNCTION_TYPES>::type Invoker;
			return Invoker::invoke(m_function.ptrFunction FUNCTION_COMMA FUNCTION_ARGS);
		}
		else if((uint32_t)m_type >= (uint32_t)typeReuse && m_type != typeAllReuse)
		{
			Detail::setCurrentFunctionReuse((uint32_t)m_type);
			typedef typename GET_MEM_FUNCTION_INVODER<R>::template Invoker<R FUNCTION_COMMA FUNCTION_TYPES>::type Invoker;
			return Invoker::invoke(m_function.memFunction.obj, m_function.memFunction.proc FUNCTION_COMMA FUNCTION_ARGS);
		}
		else
		{
			printf("FUNCTION_FUNCTION::operator() invalid function type : %u, typeid : %s\n", m_type, m_objectType);
			typedef typename GET_MEM_FUNCTION_INVODER<R>::template Invoker<R FUNCTION_COMMA FUNCTION_TYPES>::type Invoker;
			return Invoker::invoke(m_function.memFunction.obj, m_function.memFunction.proc FUNCTION_COMMA FUNCTION_ARGS);
		}
	}

	void * getObject()
	{
		return m_function.memFunction.obj;
	}

	const char* getObjectType()
	{
		return m_objectType;
	}
};

#undef FUNCTION_FUNCTION
#undef FUNCTION_COMMA
#undef FUNCTION_INVOKER
#undef FUNCTION_VOID_INVOKER
#undef GET_FUNCTION_INVODER
#undef MEM_FUNCTION_INVOKER
#undef MEM_FUNCTION_VOID_INVOKER
#undef GET_MEM_FUNCTION_INVODER

