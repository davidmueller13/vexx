namespace Detail {
template <typename Sig, bool UnlockV8>
struct FunctionForwarder<1,Sig,UnlockV8> : XFunctionSignature<Sig>
  {
  typedef XFunctionSignature<Sig> SignatureType;
  typedef char AssertArity[ (1 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;

    typedef ArgCaster<A0> AC0;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(*func)(  arg0 );
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    return CastToJS( CallNative( func, argv ) );
    }
  };

template <typename Sig, bool UnlockV8>
struct FunctionForwarderVoid<1,Sig,UnlockV8> : XFunctionSignature<Sig>
  {
  typedef XFunctionSignature<Sig> SignatureType;
  typedef char AssertArity[ (1 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;

    typedef ArgCaster<A0> AC0;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(*func)(  arg0 );
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    CallNative( func, argv );
    return v8::Undefined();
    }
  };
}
namespace Detail {
template <typename T, typename Sig, bool UnlockV8>
struct XMethodForwarder<T, 1,Sig, UnlockV8> : XMethodSignature<T,Sig>
  {
  typedef XMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (1 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;

    typedef XScriptConvert::ArgCaster<A0> AC0;

    AC0 ac0; A0 arg0(ac0.ToNative(argv.at(0)));

    Detail::Unlocker<UnlockV8> const unlocker;
    return (ReturnType)(self.*func)(  arg0 );
    }
  static XScriptValue Call( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative( self, func, argv ) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T  * self = XScriptConvert::from<T>(argv.calleeThis());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try { return XScriptConvert::to( CallNative(func, argv) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };

template <typename T, typename Sig, bool UnlockV8>
struct XMethodForwarderVoid<T, 1,Sig, UnlockV8> : XMethodSignature<T,Sig>
  {
  typedef XMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (1 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;

    typedef XScriptConvert::ArgCaster<A0> AC0;

    AC0 ac0; A0 arg0(ac0.ToNative(argv.at(0)));

    Detail::Unlocker<UnlockV8> const unlocker;
    return (ReturnType)(self.*func)(  arg0 );
    }
  static XScriptValue Call( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative( self, func, argv );
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T* self = XScriptConvert::from<T>(argv.calleeThis());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative(func, argv);
    return XScriptValue();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };
}
namespace Detail {
template <typename T, typename Sig, bool UnlockV8>
struct XConstMethodForwarder<T, 1,Sig, UnlockV8> : XConstMethodSignature<T,Sig>
  {
  typedef XConstMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (1 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;

    typedef XScriptConvert::ArgCaster<A0> AC0;

    AC0 ac0; A0 arg0(ac0.ToNative(argv.at(0)));

    Unlocker<UnlockV8> unlocker;
    return (ReturnType)(self.*func)(  arg0 );
    }
  static XScriptValue Call( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative( self, func, argv ) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T const * self = XScriptConvert::from<T>(argv.calleeThis());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try { return XScriptConvert::to( CallNative(func, argv) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };

template <typename T, typename Sig, bool UnlockV8>
struct XConstMethodForwarderVoid<T, 1,Sig, UnlockV8> : XConstMethodSignature<T,Sig>
  {
  typedef XConstMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (1 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;

    typedef ArgCaster<A0> AC0;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0 );
    }
  static XScriptValue Call( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative( self, func, argv );
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T const * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative(func, argv);
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };
}
//! Specialization for 1-arity calls.
template <>
struct CallForwarder<1>
  {
  template < typename A0>
  static XScriptValue Call( XScriptObject const & self,
                            XScriptFunction const & func,
                            A0 a0
                            )
    {
    XScriptValue args[] = {
      CastToJS(a0)
    };
    return (self.IsEmpty() || func.IsEmpty())
        ? Toss("Illegal argument: empty v8::Handle<>.")
        : func->Call(self, sizeof(args)/sizeof(args[0]), args);
    }
  template < typename A0>
  static XScriptValue Call( XScriptFunction const & func,
                            A0 a0
                            )
    {
    return Call( func, func, a0 );
    }

  };
namespace Detail {

template <typename Sig>
struct CtorForwarderProxy<Sig,1>
  {
  enum { Arity = 1 };
  typedef typename XSignature<Sig>::ReturnType ReturnType;
  static ReturnType Call( XScriptArguments const & argv )
    {
    if( argv.length() < Arity )
      {
      throw std::range_error("CtorForwarder<T,1>::Ctor() expects at least 1 JS arguments!");
      }
    else
      {
      typedef typename sl::At< 0, XSignature<Sig> >::Type A0;

      typedef XScriptConvert::ArgCaster<A0> AC0;

      AC0 ac0; A0 arg0(ac0.ToNative(argv.at(0)));
      (void)arg0;

      typedef typename XScriptTypeInfo<ReturnType>::Type Type;
      return new Type(  arg0 );
      }
    }
  };
}
namespace Detail {
template <typename Sig, bool UnlockV8>
struct FunctionForwarder<2,Sig,UnlockV8> : XFunctionSignature<Sig>
  {
  typedef XFunctionSignature<Sig> SignatureType;
  typedef char AssertArity[ (2 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(*func)(  arg0, arg1 );
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    return CastToJS( CallNative( func, argv ) );
    }
  };

template <typename Sig, bool UnlockV8>
struct FunctionForwarderVoid<2,Sig,UnlockV8> : XFunctionSignature<Sig>
  {
  typedef XFunctionSignature<Sig> SignatureType;
  typedef char AssertArity[ (2 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(*func)(  arg0, arg1 );
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    CallNative( func, argv );
    return v8::Undefined();
    }
  };
}
namespace Detail {
template <typename T, typename Sig, bool UnlockV8>
struct XMethodForwarder<T, 2,Sig, UnlockV8> : XMethodSignature<T,Sig>
  {
  typedef XMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (2 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;

    typedef XScriptConvert::ArgCaster<A0> AC0;
    typedef XScriptConvert::ArgCaster<A1> AC1;

    AC0 ac0; A0 arg0(ac0.ToNative(argv.at(0)));
    AC1 ac1; A1 arg1(ac1.ToNative(argv.at(1)));

    Unlocker<UnlockV8> unlocker;
    return (ReturnType)(self.*func)(  arg0, arg1 );
    }
  static XScriptValue Call( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative( self, func, argv ) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T  * self = XScriptConvert::from<T>(argv.calleeThis());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try { return XScriptConvert::to( CallNative(func, argv) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };

template <typename T, typename Sig, bool UnlockV8>
struct XMethodForwarderVoid<T, 2,Sig, UnlockV8> : XMethodSignature<T,Sig>
  {
  typedef XMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (2 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1 );
    }
  static XScriptValue Call( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative( self, func, argv );
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T  * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative(func, argv);
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };
}
namespace Detail {
template <typename T, typename Sig, bool UnlockV8>
struct XConstMethodForwarder<T, 2,Sig, UnlockV8> : XConstMethodSignature<T,Sig>
  {
  typedef XConstMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (2 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1 );
    }
  static XScriptValue Call( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative( self, func, argv ) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T const * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative(func, argv) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };

template <typename T, typename Sig, bool UnlockV8>
struct XConstMethodForwarderVoid<T, 2,Sig, UnlockV8> : XConstMethodSignature<T,Sig>
  {
  typedef XConstMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (2 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1 );
    }
  static XScriptValue Call( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative( self, func, argv );
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T const * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative(func, argv);
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };
}
//! Specialization for 2-arity calls.
template <>
struct CallForwarder<2>
  {
  template < typename A0, typename A1>
  static XScriptValue Call( XScriptObject const & self,
                            XScriptFunction const & func,
                            A0 a0, A1 a1
                            )
    {
    XScriptValue args[] = {
      CastToJS(a0), CastToJS(a1)
    };
    return (self.IsEmpty() || func.IsEmpty())
        ? Toss("Illegal argument: empty v8::Handle<>.")
        : func->Call(self, sizeof(args)/sizeof(args[0]), args);
    }
  template < typename A0, typename A1>
  static XScriptValue Call( XScriptFunction const & func,
                            A0 a0, A1 a1
                            )
    {
    return Call( func, func, a0,a1 );
    }

  };
namespace Detail {
template <typename Sig>
struct CtorForwarderProxy<Sig,2>
  {
  enum { Arity = 2 };
  typedef typename XSignature<Sig>::ReturnType ReturnType;
  static ReturnType Call( XScriptArguments const & argv )
    {
    if( argv.Length() < Arity )
      {
      throw std::range_error("CtorForwarder<T,2>::Ctor() expects at least 2 JS arguments!");
      }
    else
      {
      typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
      typedef typename sl::At< 1, XSignature<Sig> >::Type A1;

      typedef ArgCaster<A0> AC0;
      typedef ArgCaster<A1> AC1;

      AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
      AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));

      typedef typename XScriptTypeInfo<ReturnType>::Type Type;
      return new Type(  arg0, arg1 );
      }
    }
  };
}
namespace Detail {
template <typename Sig, bool UnlockV8>
struct FunctionForwarder<3,Sig,UnlockV8> : XFunctionSignature<Sig>
  {
  typedef XFunctionSignature<Sig> SignatureType;
  typedef char AssertArity[ (3 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(*func)(  arg0, arg1, arg2 );
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    return CastToJS( CallNative( func, argv ) );
    }
  };

template <typename Sig, bool UnlockV8>
struct FunctionForwarderVoid<3,Sig,UnlockV8> : XFunctionSignature<Sig>
  {
  typedef XFunctionSignature<Sig> SignatureType;
  typedef char AssertArity[ (3 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(*func)(  arg0, arg1, arg2 );
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    CallNative( func, argv );
    return v8::Undefined();
    }
  };
}
namespace Detail {
template <typename T, typename Sig, bool UnlockV8>
struct XMethodForwarder<T, 3,Sig, UnlockV8> : XMethodSignature<T,Sig>
  {
  typedef XMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (3 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;

    typedef XScriptConvert::ArgCaster<A0> AC0;
    typedef XScriptConvert::ArgCaster<A1> AC1;
    typedef XScriptConvert::ArgCaster<A2> AC2;

    AC0 ac0; A0 arg0(ac0.ToNative(argv.at(0)));
    AC1 ac1; A1 arg1(ac1.ToNative(argv.at(1)));
    AC2 ac2; A2 arg2(ac2.ToNative(argv.at(2)));

    Unlocker<UnlockV8> unlocker;
    return (ReturnType)(self.*func)(  arg0, arg1, arg2 );
    }
  static XScriptValue Call( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative( self, func, argv ) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T  * self = XScriptConvert::from<T>(argv.calleeThis());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try { return XScriptConvert::to( CallNative(func, argv) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };

template <typename T, typename Sig, bool UnlockV8>
struct XMethodForwarderVoid<T, 3,Sig, UnlockV8> : XMethodSignature<T,Sig>
  {
  typedef XMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (3 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2 );
    }
  static XScriptValue Call( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative( self, func, argv );
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T  * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative(func, argv);
    return XScriptValue();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };
}
namespace Detail {
template <typename T, typename Sig, bool UnlockV8>
struct XConstMethodForwarder<T, 3,Sig, UnlockV8> : XConstMethodSignature<T,Sig>
  {
  typedef XConstMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (3 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2 );
    }
  static XScriptValue Call( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative( self, func, argv ) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T const * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative(func, argv) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };

template <typename T, typename Sig, bool UnlockV8>
struct XConstMethodForwarderVoid<T, 3,Sig, UnlockV8> : XConstMethodSignature<T,Sig>
  {
  typedef XConstMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (3 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2 );
    }
  static XScriptValue Call( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative( self, func, argv );
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T const * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative(func, argv);
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };
}
//! Specialization for 3-arity calls.
template <>
struct CallForwarder<3>
  {
  template < typename A0, typename A1, typename A2>
  static XScriptValue Call( XScriptObject const & self,
                            XScriptFunction const & func,
                            A0 a0, A1 a1, A2 a2
                            )
    {
    XScriptValue args[] = {
      CastToJS(a0), CastToJS(a1), CastToJS(a2)
    };
    return (self.IsEmpty() || func.IsEmpty())
        ? Toss("Illegal argument: empty v8::Handle<>.")
        : func->Call(self, sizeof(args)/sizeof(args[0]), args);
    }
  template < typename A0, typename A1, typename A2>
  static XScriptValue Call( XScriptFunction const & func,
                            A0 a0, A1 a1, A2 a2
                            )
    {
    return Call( func, func, a0,a1,a2 );
    }

  };
namespace Detail {
template <typename Sig>
struct CtorForwarderProxy<Sig,3>
  {
  enum { Arity = 3 };
  typedef typename XSignature<Sig>::ReturnType ReturnType;
  static ReturnType Call( XScriptArguments const & argv )
    {
    if( argv.Length() < Arity )
      {
      throw std::range_error("CtorForwarder<T,3>::Ctor() expects at least 3 JS arguments!");
      }
    else
      {
      typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
      typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
      typedef typename sl::At< 2, XSignature<Sig> >::Type A2;

      typedef ArgCaster<A0> AC0;
      typedef ArgCaster<A1> AC1;
      typedef ArgCaster<A2> AC2;

      AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
      AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
      AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));

      typedef typename XScriptTypeInfo<ReturnType>::Type Type;
      return new Type(  arg0, arg1, arg2 );
      }
    }
  };
}
namespace Detail {
template <typename Sig, bool UnlockV8>
struct FunctionForwarder<4,Sig,UnlockV8> : XFunctionSignature<Sig>
  {
  typedef XFunctionSignature<Sig> SignatureType;
  typedef char AssertArity[ (4 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(*func)(  arg0, arg1, arg2, arg3 );
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    return CastToJS( CallNative( func, argv ) );
    }
  };

template <typename Sig, bool UnlockV8>
struct FunctionForwarderVoid<4,Sig,UnlockV8> : XFunctionSignature<Sig>
  {
  typedef XFunctionSignature<Sig> SignatureType;
  typedef char AssertArity[ (4 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(*func)(  arg0, arg1, arg2, arg3 );
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    CallNative( func, argv );
    return v8::Undefined();
    }
  };
}
namespace Detail {
template <typename T, typename Sig, bool UnlockV8>
struct XMethodForwarder<T, 4,Sig, UnlockV8> : XMethodSignature<T,Sig>
  {
  typedef XMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (4 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3 );
    }
  static XScriptValue Call( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative( self, func, argv ) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T  * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative(func, argv) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };

template <typename T, typename Sig, bool UnlockV8>
struct XMethodForwarderVoid<T, 4,Sig, UnlockV8> : XMethodSignature<T,Sig>
  {
  typedef XMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (4 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3 );
    }
  static XScriptValue Call( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative( self, func, argv );
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T  * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative(func, argv);
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };
}
namespace Detail {
template <typename T, typename Sig, bool UnlockV8>
struct XConstMethodForwarder<T, 4,Sig, UnlockV8> : XConstMethodSignature<T,Sig>
  {
  typedef XConstMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (4 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3 );
    }
  static XScriptValue Call( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative( self, func, argv ) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T const * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative(func, argv) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };

template <typename T, typename Sig, bool UnlockV8>
struct XConstMethodForwarderVoid<T, 4,Sig, UnlockV8> : XConstMethodSignature<T,Sig>
  {
  typedef XConstMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (4 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3 );
    }
  static XScriptValue Call( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative( self, func, argv );
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T const * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative(func, argv);
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };
}
//! Specialization for 4-arity calls.
template <>
struct CallForwarder<4>
  {
  template < typename A0, typename A1, typename A2, typename A3>
  static XScriptValue Call( XScriptObject const & self,
                            XScriptFunction const & func,
                            A0 a0, A1 a1, A2 a2, A3 a3
                            )
    {
    XScriptValue args[] = {
      CastToJS(a0), CastToJS(a1), CastToJS(a2), CastToJS(a3)
    };
    return (self.IsEmpty() || func.IsEmpty())
        ? Toss("Illegal argument: empty v8::Handle<>.")
        : func->Call(self, sizeof(args)/sizeof(args[0]), args);
    }
  template < typename A0, typename A1, typename A2, typename A3>
  static XScriptValue Call( XScriptFunction const & func,
                            A0 a0, A1 a1, A2 a2, A3 a3
                            )
    {
    return Call( func, func, a0,a1,a2,a3 );
    }

  };
namespace Detail {
template <typename Sig>
struct CtorForwarderProxy<Sig,4>
  {
  enum { Arity = 4 };
  typedef typename XSignature<Sig>::ReturnType ReturnType;
  static ReturnType Call( XScriptArguments const & argv )
    {
    if( argv.Length() < Arity )
      {
      throw std::range_error("CtorForwarder<T,4>::Ctor() expects at least 4 JS arguments!");
      }
    else
      {
      typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
      typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
      typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
      typedef typename sl::At< 3, XSignature<Sig> >::Type A3;

      typedef ArgCaster<A0> AC0;
      typedef ArgCaster<A1> AC1;
      typedef ArgCaster<A2> AC2;
      typedef ArgCaster<A3> AC3;

      AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
      AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
      AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
      AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));

      typedef typename XScriptTypeInfo<ReturnType>::Type Type;
      return new Type(  arg0, arg1, arg2, arg3 );
      }
    }
  };
}
namespace Detail {
template <typename Sig, bool UnlockV8>
struct FunctionForwarder<5,Sig,UnlockV8> : XFunctionSignature<Sig>
  {
  typedef XFunctionSignature<Sig> SignatureType;
  typedef char AssertArity[ (5 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(*func)(  arg0, arg1, arg2, arg3, arg4 );
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    return CastToJS( CallNative( func, argv ) );
    }
  };

template <typename Sig, bool UnlockV8>
struct FunctionForwarderVoid<5,Sig,UnlockV8> : XFunctionSignature<Sig>
  {
  typedef XFunctionSignature<Sig> SignatureType;
  typedef char AssertArity[ (5 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(*func)(  arg0, arg1, arg2, arg3, arg4 );
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    CallNative( func, argv );
    return v8::Undefined();
    }
  };
}
namespace Detail {
template <typename T, typename Sig, bool UnlockV8>
struct XMethodForwarder<T, 5,Sig, UnlockV8> : XMethodSignature<T,Sig>
  {
  typedef XMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (5 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4 );
    }
  static XScriptValue Call( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative( self, func, argv ) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T  * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative(func, argv) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };

template <typename T, typename Sig, bool UnlockV8>
struct XMethodForwarderVoid<T, 5,Sig, UnlockV8> : XMethodSignature<T,Sig>
  {
  typedef XMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (5 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;

    typedef XScriptConvert::ArgCaster<A0> AC0;
    typedef XScriptConvert::ArgCaster<A1> AC1;
    typedef XScriptConvert::ArgCaster<A2> AC2;
    typedef XScriptConvert::ArgCaster<A3> AC3;
    typedef XScriptConvert::ArgCaster<A4> AC4;

    AC0 ac0; A0 arg0(ac0.ToNative(argv.at(0)));
    AC1 ac1; A1 arg1(ac1.ToNative(argv.at(1)));
    AC2 ac2; A2 arg2(ac2.ToNative(argv.at(2)));
    AC3 ac3; A3 arg3(ac3.ToNative(argv.at(3)));
    AC4 ac4; A4 arg4(ac4.ToNative(argv.at(4)));

    Unlocker<UnlockV8> unlocker;
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4 );
    }
  static XScriptValue Call( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative( self, func, argv );
    return XScriptValue();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T  * self = XScriptConvert::from<T>(argv.calleeThis());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative(func, argv);
    return XScriptValue();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };
}
namespace Detail {
template <typename T, typename Sig, bool UnlockV8>
struct XConstMethodForwarder<T, 5,Sig, UnlockV8> : XConstMethodSignature<T,Sig>
  {
  typedef XConstMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (5 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4 );
    }
  static XScriptValue Call( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative( self, func, argv ) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T const * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative(func, argv) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };

template <typename T, typename Sig, bool UnlockV8>
struct XConstMethodForwarderVoid<T, 5,Sig, UnlockV8> : XConstMethodSignature<T,Sig>
  {
  typedef XConstMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (5 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4 );
    }
  static XScriptValue Call( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative( self, func, argv );
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T const * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative(func, argv);
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };
}
//! Specialization for 5-arity calls.
template <>
struct CallForwarder<5>
  {
  template < typename A0, typename A1, typename A2, typename A3, typename A4>
  static XScriptValue Call( XScriptObject const & self,
                            XScriptFunction const & func,
                            A0 a0, A1 a1, A2 a2, A3 a3, A4 a4
                            )
    {
    XScriptValue args[] = {
      CastToJS(a0), CastToJS(a1), CastToJS(a2), CastToJS(a3), CastToJS(a4)
    };
    return (self.IsEmpty() || func.IsEmpty())
        ? Toss("Illegal argument: empty v8::Handle<>.")
        : func->Call(self, sizeof(args)/sizeof(args[0]), args);
    }
  template < typename A0, typename A1, typename A2, typename A3, typename A4>
  static XScriptValue Call( XScriptFunction const & func,
                            A0 a0, A1 a1, A2 a2, A3 a3, A4 a4
                            )
    {
    return Call( func, func, a0,a1,a2,a3,a4 );
    }

  };
namespace Detail {
template <typename Sig>
struct CtorForwarderProxy<Sig,5>
  {
  enum { Arity = 5 };
  typedef typename XSignature<Sig>::ReturnType ReturnType;
  static ReturnType Call( XScriptArguments const & argv )
    {
    if( argv.Length() < Arity )
      {
      throw std::range_error("CtorForwarder<T,5>::Ctor() expects at least 5 JS arguments!");
      }
    else
      {
      typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
      typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
      typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
      typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
      typedef typename sl::At< 4, XSignature<Sig> >::Type A4;

      typedef ArgCaster<A0> AC0;
      typedef ArgCaster<A1> AC1;
      typedef ArgCaster<A2> AC2;
      typedef ArgCaster<A3> AC3;
      typedef ArgCaster<A4> AC4;

      AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
      AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
      AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
      AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
      AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));

      typedef typename XScriptTypeInfo<ReturnType>::Type Type;
      return new Type(  arg0, arg1, arg2, arg3, arg4 );
      }
    }
  };
}
namespace Detail {
template <typename Sig, bool UnlockV8>
struct FunctionForwarder<6,Sig,UnlockV8> : XFunctionSignature<Sig>
  {
  typedef XFunctionSignature<Sig> SignatureType;
  typedef char AssertArity[ (6 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(*func)(  arg0, arg1, arg2, arg3, arg4, arg5 );
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    return CastToJS( CallNative( func, argv ) );
    }
  };

template <typename Sig, bool UnlockV8>
struct FunctionForwarderVoid<6,Sig,UnlockV8> : XFunctionSignature<Sig>
  {
  typedef XFunctionSignature<Sig> SignatureType;
  typedef char AssertArity[ (6 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(*func)(  arg0, arg1, arg2, arg3, arg4, arg5 );
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    CallNative( func, argv );
    return v8::Undefined();
    }
  };
}
namespace Detail {
template <typename T, typename Sig, bool UnlockV8>
struct XMethodForwarder<T, 6,Sig, UnlockV8> : XMethodSignature<T,Sig>
  {
  typedef XMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (6 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4, arg5 );
    }
  static XScriptValue Call( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative( self, func, argv ) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T  * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative(func, argv) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };

template <typename T, typename Sig, bool UnlockV8>
struct XMethodForwarderVoid<T, 6,Sig, UnlockV8> : XMethodSignature<T,Sig>
  {
  typedef XMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (6 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4, arg5 );
    }
  static XScriptValue Call( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative( self, func, argv );
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T  * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative(func, argv);
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };
}
namespace Detail {
template <typename T, typename Sig, bool UnlockV8>
struct XConstMethodForwarder<T, 6,Sig, UnlockV8> : XConstMethodSignature<T,Sig>
  {
  typedef XConstMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (6 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4, arg5 );
    }
  static XScriptValue Call( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative( self, func, argv ) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T const * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative(func, argv) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };

template <typename T, typename Sig, bool UnlockV8>
struct XConstMethodForwarderVoid<T, 6,Sig, UnlockV8> : XConstMethodSignature<T,Sig>
  {
  typedef XConstMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (6 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4, arg5 );
    }
  static XScriptValue Call( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative( self, func, argv );
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T const * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative(func, argv);
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };
}
//! Specialization for 6-arity calls.
template <>
struct CallForwarder<6>
  {
  template < typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
  static XScriptValue Call( XScriptObject const & self,
                            XScriptFunction const & func,
                            A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5
                            )
    {
    XScriptValue args[] = {
      CastToJS(a0), CastToJS(a1), CastToJS(a2), CastToJS(a3), CastToJS(a4), CastToJS(a5)
    };
    return (self.IsEmpty() || func.IsEmpty())
        ? Toss("Illegal argument: empty v8::Handle<>.")
        : func->Call(self, sizeof(args)/sizeof(args[0]), args);
    }
  template < typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
  static XScriptValue Call( XScriptFunction const & func,
                            A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5
                            )
    {
    return Call( func, func, a0,a1,a2,a3,a4,a5 );
    }

  };
namespace Detail {
template <typename Sig>
struct CtorForwarderProxy<Sig,6>
  {
  enum { Arity = 6 };
  typedef typename XSignature<Sig>::ReturnType ReturnType;
  static ReturnType Call( XScriptArguments const & argv )
    {
    if( argv.Length() < Arity )
      {
      throw std::range_error("CtorForwarder<T,6>::Ctor() expects at least 6 JS arguments!");
      }
    else
      {
      typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
      typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
      typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
      typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
      typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
      typedef typename sl::At< 5, XSignature<Sig> >::Type A5;

      typedef ArgCaster<A0> AC0;
      typedef ArgCaster<A1> AC1;
      typedef ArgCaster<A2> AC2;
      typedef ArgCaster<A3> AC3;
      typedef ArgCaster<A4> AC4;
      typedef ArgCaster<A5> AC5;

      AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
      AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
      AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
      AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
      AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
      AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));

      typedef typename XScriptTypeInfo<ReturnType>::Type Type;
      return new Type(  arg0, arg1, arg2, arg3, arg4, arg5 );
      }
    }
  };
}
namespace Detail {
template <typename Sig, bool UnlockV8>
struct FunctionForwarder<7,Sig,UnlockV8> : XFunctionSignature<Sig>
  {
  typedef XFunctionSignature<Sig> SignatureType;
  typedef char AssertArity[ (7 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6 );
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    return CastToJS( CallNative( func, argv ) );
    }
  };

template <typename Sig, bool UnlockV8>
struct FunctionForwarderVoid<7,Sig,UnlockV8> : XFunctionSignature<Sig>
  {
  typedef XFunctionSignature<Sig> SignatureType;
  typedef char AssertArity[ (7 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6 );
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    CallNative( func, argv );
    return v8::Undefined();
    }
  };
}
namespace Detail {
template <typename T, typename Sig, bool UnlockV8>
struct XMethodForwarder<T, 7,Sig, UnlockV8> : XMethodSignature<T,Sig>
  {
  typedef XMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (7 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6 );
    }
  static XScriptValue Call( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative( self, func, argv ) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T  * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative(func, argv) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };

template <typename T, typename Sig, bool UnlockV8>
struct XMethodForwarderVoid<T, 7,Sig, UnlockV8> : XMethodSignature<T,Sig>
  {
  typedef XMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (7 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6 );
    }
  static XScriptValue Call( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative( self, func, argv );
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T  * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative(func, argv);
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };
}
namespace Detail {
template <typename T, typename Sig, bool UnlockV8>
struct XConstMethodForwarder<T, 7,Sig, UnlockV8> : XConstMethodSignature<T,Sig>
  {
  typedef XConstMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (7 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6 );
    }
  static XScriptValue Call( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative( self, func, argv ) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T const * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative(func, argv) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };

template <typename T, typename Sig, bool UnlockV8>
struct XConstMethodForwarderVoid<T, 7,Sig, UnlockV8> : XConstMethodSignature<T,Sig>
  {
  typedef XConstMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (7 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6 );
    }
  static XScriptValue Call( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative( self, func, argv );
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T const * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative(func, argv);
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };
}
//! Specialization for 7-arity calls.
template <>
struct CallForwarder<7>
  {
  template < typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
  static XScriptValue Call( XScriptObject const & self,
                            XScriptFunction const & func,
                            A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6
                            )
    {
    XScriptValue args[] = {
      CastToJS(a0), CastToJS(a1), CastToJS(a2), CastToJS(a3), CastToJS(a4), CastToJS(a5), CastToJS(a6)
    };
    return (self.IsEmpty() || func.IsEmpty())
        ? Toss("Illegal argument: empty v8::Handle<>.")
        : func->Call(self, sizeof(args)/sizeof(args[0]), args);
    }
  template < typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
  static XScriptValue Call( XScriptFunction const & func,
                            A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6
                            )
    {
    return Call( func, func, a0,a1,a2,a3,a4,a5,a6 );
    }

  };
namespace Detail {
template <typename Sig>
struct CtorForwarderProxy<Sig,7>
  {
  enum { Arity = 7 };
  typedef typename XSignature<Sig>::ReturnType ReturnType;
  static ReturnType Call( XScriptArguments const & argv )
    {
    if( argv.Length() < Arity )
      {
      throw std::range_error("CtorForwarder<T,7>::Ctor() expects at least 7 JS arguments!");
      }
    else
      {
      typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
      typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
      typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
      typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
      typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
      typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
      typedef typename sl::At< 6, XSignature<Sig> >::Type A6;

      typedef ArgCaster<A0> AC0;
      typedef ArgCaster<A1> AC1;
      typedef ArgCaster<A2> AC2;
      typedef ArgCaster<A3> AC3;
      typedef ArgCaster<A4> AC4;
      typedef ArgCaster<A5> AC5;
      typedef ArgCaster<A6> AC6;

      AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
      AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
      AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
      AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
      AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
      AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
      AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));

      typedef typename XScriptTypeInfo<ReturnType>::Type Type;
      return new Type(  arg0, arg1, arg2, arg3, arg4, arg5, arg6 );
      }
    }
  };
}
namespace Detail {
template <typename Sig, bool UnlockV8>
struct FunctionForwarder<8,Sig,UnlockV8> : XFunctionSignature<Sig>
  {
  typedef XFunctionSignature<Sig> SignatureType;
  typedef char AssertArity[ (8 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;
    typedef typename sl::At< 7, XSignature<Sig> >::Type A7;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;
    typedef ArgCaster<A7> AC7;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
    AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7 );
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    return CastToJS( CallNative( func, argv ) );
    }
  };

template <typename Sig, bool UnlockV8>
struct FunctionForwarderVoid<8,Sig,UnlockV8> : XFunctionSignature<Sig>
  {
  typedef XFunctionSignature<Sig> SignatureType;
  typedef char AssertArity[ (8 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;
    typedef typename sl::At< 7, XSignature<Sig> >::Type A7;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;
    typedef ArgCaster<A7> AC7;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
    AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7 );
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    CallNative( func, argv );
    return v8::Undefined();
    }
  };
}
namespace Detail {
template <typename T, typename Sig, bool UnlockV8>
struct XMethodForwarder<T, 8,Sig, UnlockV8> : XMethodSignature<T,Sig>
  {
  typedef XMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (8 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;
    typedef typename sl::At< 7, XSignature<Sig> >::Type A7;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;
    typedef ArgCaster<A7> AC7;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
    AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7 );
    }
  static XScriptValue Call( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative( self, func, argv ) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T  * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative(func, argv) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };

template <typename T, typename Sig, bool UnlockV8>
struct XMethodForwarderVoid<T, 8,Sig, UnlockV8> : XMethodSignature<T,Sig>
  {
  typedef XMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (8 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;
    typedef typename sl::At< 7, XSignature<Sig> >::Type A7;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;
    typedef ArgCaster<A7> AC7;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
    AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7 );
    }
  static XScriptValue Call( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative( self, func, argv );
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T  * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative(func, argv);
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };
}
namespace Detail {
template <typename T, typename Sig, bool UnlockV8>
struct XConstMethodForwarder<T, 8,Sig, UnlockV8> : XConstMethodSignature<T,Sig>
  {
  typedef XConstMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (8 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;
    typedef typename sl::At< 7, XSignature<Sig> >::Type A7;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;
    typedef ArgCaster<A7> AC7;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
    AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7 );
    }
  static XScriptValue Call( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative( self, func, argv ) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T const * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative(func, argv) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };

template <typename T, typename Sig, bool UnlockV8>
struct XConstMethodForwarderVoid<T, 8,Sig, UnlockV8> : XConstMethodSignature<T,Sig>
  {
  typedef XConstMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (8 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;
    typedef typename sl::At< 7, XSignature<Sig> >::Type A7;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;
    typedef ArgCaster<A7> AC7;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
    AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7 );
    }
  static XScriptValue Call( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative( self, func, argv );
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T const * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative(func, argv);
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };
}
//! Specialization for 8-arity calls.
template <>
struct CallForwarder<8>
  {
  template < typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
  static XScriptValue Call( XScriptObject const & self,
                            XScriptFunction const & func,
                            A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7
                            )
    {
    XScriptValue args[] = {
      CastToJS(a0), CastToJS(a1), CastToJS(a2), CastToJS(a3), CastToJS(a4), CastToJS(a5), CastToJS(a6), CastToJS(a7)
    };
    return (self.IsEmpty() || func.IsEmpty())
        ? Toss("Illegal argument: empty v8::Handle<>.")
        : func->Call(self, sizeof(args)/sizeof(args[0]), args);
    }
  template < typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
  static XScriptValue Call( XScriptFunction const & func,
                            A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7
                            )
    {
    return Call( func, func, a0,a1,a2,a3,a4,a5,a6,a7 );
    }

  };
namespace Detail {
template <typename Sig>
struct CtorForwarderProxy<Sig,8>
  {
  enum { Arity = 8 };
  typedef typename XSignature<Sig>::ReturnType ReturnType;
  static ReturnType Call( XScriptArguments const & argv )
    {
    if( argv.Length() < Arity )
      {
      throw std::range_error("CtorForwarder<T,8>::Ctor() expects at least 8 JS arguments!");
      }
    else
      {
      typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
      typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
      typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
      typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
      typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
      typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
      typedef typename sl::At< 6, XSignature<Sig> >::Type A6;
      typedef typename sl::At< 7, XSignature<Sig> >::Type A7;

      typedef ArgCaster<A0> AC0;
      typedef ArgCaster<A1> AC1;
      typedef ArgCaster<A2> AC2;
      typedef ArgCaster<A3> AC3;
      typedef ArgCaster<A4> AC4;
      typedef ArgCaster<A5> AC5;
      typedef ArgCaster<A6> AC6;
      typedef ArgCaster<A7> AC7;

      AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
      AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
      AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
      AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
      AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
      AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
      AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
      AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));

      typedef typename XScriptTypeInfo<ReturnType>::Type Type;
      return new Type(  arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7 );
      }
    }
  };
}
namespace Detail {
template <typename Sig, bool UnlockV8>
struct FunctionForwarder<9,Sig,UnlockV8> : XFunctionSignature<Sig>
  {
  typedef XFunctionSignature<Sig> SignatureType;
  typedef char AssertArity[ (9 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;
    typedef typename sl::At< 7, XSignature<Sig> >::Type A7;
    typedef typename sl::At< 8, XSignature<Sig> >::Type A8;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;
    typedef ArgCaster<A7> AC7;
    typedef ArgCaster<A8> AC8;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
    AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));
    AC8 ac8; A8 arg8(ac8.ToNative(argv[8]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8 );
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    return CastToJS( CallNative( func, argv ) );
    }
  };

template <typename Sig, bool UnlockV8>
struct FunctionForwarderVoid<9,Sig,UnlockV8> : XFunctionSignature<Sig>
  {
  typedef XFunctionSignature<Sig> SignatureType;
  typedef char AssertArity[ (9 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;
    typedef typename sl::At< 7, XSignature<Sig> >::Type A7;
    typedef typename sl::At< 8, XSignature<Sig> >::Type A8;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;
    typedef ArgCaster<A7> AC7;
    typedef ArgCaster<A8> AC8;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
    AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));
    AC8 ac8; A8 arg8(ac8.ToNative(argv[8]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8 );
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    CallNative( func, argv );
    return v8::Undefined();
    }
  };
}
namespace Detail {
template <typename T, typename Sig, bool UnlockV8>
struct XMethodForwarder<T, 9,Sig, UnlockV8> : XMethodSignature<T,Sig>
  {
  typedef XMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (9 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;
    typedef typename sl::At< 7, XSignature<Sig> >::Type A7;
    typedef typename sl::At< 8, XSignature<Sig> >::Type A8;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;
    typedef ArgCaster<A7> AC7;
    typedef ArgCaster<A8> AC8;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
    AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));
    AC8 ac8; A8 arg8(ac8.ToNative(argv[8]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8 );
    }
  static XScriptValue Call( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative( self, func, argv ) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T  * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative(func, argv) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };

template <typename T, typename Sig, bool UnlockV8>
struct XMethodForwarderVoid<T, 9,Sig, UnlockV8> : XMethodSignature<T,Sig>
  {
  typedef XMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (9 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;
    typedef typename sl::At< 7, XSignature<Sig> >::Type A7;
    typedef typename sl::At< 8, XSignature<Sig> >::Type A8;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;
    typedef ArgCaster<A7> AC7;
    typedef ArgCaster<A8> AC8;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
    AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));
    AC8 ac8; A8 arg8(ac8.ToNative(argv[8]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8 );
    }
  static XScriptValue Call( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative( self, func, argv );
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T  * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative(func, argv);
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };
}
namespace Detail {
template <typename T, typename Sig, bool UnlockV8>
struct XConstMethodForwarder<T, 9,Sig, UnlockV8> : XConstMethodSignature<T,Sig>
  {
  typedef XConstMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (9 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;
    typedef typename sl::At< 7, XSignature<Sig> >::Type A7;
    typedef typename sl::At< 8, XSignature<Sig> >::Type A8;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;
    typedef ArgCaster<A7> AC7;
    typedef ArgCaster<A8> AC8;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
    AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));
    AC8 ac8; A8 arg8(ac8.ToNative(argv[8]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8 );
    }
  static XScriptValue Call( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative( self, func, argv ) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T const * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative(func, argv) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };

template <typename T, typename Sig, bool UnlockV8>
struct XConstMethodForwarderVoid<T, 9,Sig, UnlockV8> : XConstMethodSignature<T,Sig>
  {
  typedef XConstMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (9 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;
    typedef typename sl::At< 7, XSignature<Sig> >::Type A7;
    typedef typename sl::At< 8, XSignature<Sig> >::Type A8;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;
    typedef ArgCaster<A7> AC7;
    typedef ArgCaster<A8> AC8;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
    AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));
    AC8 ac8; A8 arg8(ac8.ToNative(argv[8]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8 );
    }
  static XScriptValue Call( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative( self, func, argv );
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T const * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative(func, argv);
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };
}
//! Specialization for 9-arity calls.
template <>
struct CallForwarder<9>
  {
  template < typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
  static XScriptValue Call( XScriptObject const & self,
                            XScriptFunction const & func,
                            A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8
                            )
    {
    XScriptValue args[] = {
      CastToJS(a0), CastToJS(a1), CastToJS(a2), CastToJS(a3), CastToJS(a4), CastToJS(a5), CastToJS(a6), CastToJS(a7), CastToJS(a8)
    };
    return (self.IsEmpty() || func.IsEmpty())
        ? Toss("Illegal argument: empty v8::Handle<>.")
        : func->Call(self, sizeof(args)/sizeof(args[0]), args);
    }
  template < typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
  static XScriptValue Call( XScriptFunction const & func,
                            A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8
                            )
    {
    return Call( func, func, a0,a1,a2,a3,a4,a5,a6,a7,a8 );
    }

  };
namespace Detail {
template <typename Sig>
struct CtorForwarderProxy<Sig,9>
  {
  enum { Arity = 9 };
  typedef typename XSignature<Sig>::ReturnType ReturnType;
  static ReturnType Call( XScriptArguments const & argv )
    {
    if( argv.Length() < Arity )
      {
      throw std::range_error("CtorForwarder<T,9>::Ctor() expects at least 9 JS arguments!");
      }
    else
      {
      typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
      typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
      typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
      typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
      typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
      typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
      typedef typename sl::At< 6, XSignature<Sig> >::Type A6;
      typedef typename sl::At< 7, XSignature<Sig> >::Type A7;
      typedef typename sl::At< 8, XSignature<Sig> >::Type A8;

      typedef ArgCaster<A0> AC0;
      typedef ArgCaster<A1> AC1;
      typedef ArgCaster<A2> AC2;
      typedef ArgCaster<A3> AC3;
      typedef ArgCaster<A4> AC4;
      typedef ArgCaster<A5> AC5;
      typedef ArgCaster<A6> AC6;
      typedef ArgCaster<A7> AC7;
      typedef ArgCaster<A8> AC8;

      AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
      AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
      AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
      AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
      AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
      AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
      AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
      AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));
      AC8 ac8; A8 arg8(ac8.ToNative(argv[8]));

      typedef typename XScriptTypeInfo<ReturnType>::Type Type;
      return new Type(  arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8 );
      }
    }
  };
}
namespace Detail {
template <typename Sig, bool UnlockV8>
struct FunctionForwarder<10,Sig,UnlockV8> : XFunctionSignature<Sig>
  {
  typedef XFunctionSignature<Sig> SignatureType;
  typedef char AssertArity[ (10 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;
    typedef typename sl::At< 7, XSignature<Sig> >::Type A7;
    typedef typename sl::At< 8, XSignature<Sig> >::Type A8;
    typedef typename sl::At< 9, XSignature<Sig> >::Type A9;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;
    typedef ArgCaster<A7> AC7;
    typedef ArgCaster<A8> AC8;
    typedef ArgCaster<A9> AC9;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
    AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));
    AC8 ac8; A8 arg8(ac8.ToNative(argv[8]));
    AC9 ac9; A9 arg9(ac9.ToNative(argv[9]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9 );
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    return CastToJS( CallNative( func, argv ) );
    }
  };

template <typename Sig, bool UnlockV8>
struct FunctionForwarderVoid<10,Sig,UnlockV8> : XFunctionSignature<Sig>
  {
  typedef XFunctionSignature<Sig> SignatureType;
  typedef char AssertArity[ (10 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;
    typedef typename sl::At< 7, XSignature<Sig> >::Type A7;
    typedef typename sl::At< 8, XSignature<Sig> >::Type A8;
    typedef typename sl::At< 9, XSignature<Sig> >::Type A9;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;
    typedef ArgCaster<A7> AC7;
    typedef ArgCaster<A8> AC8;
    typedef ArgCaster<A9> AC9;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
    AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));
    AC8 ac8; A8 arg8(ac8.ToNative(argv[8]));
    AC9 ac9; A9 arg9(ac9.ToNative(argv[9]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9 );
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    CallNative( func, argv );
    return v8::Undefined();
    }
  };
}
namespace Detail {
template <typename T, typename Sig, bool UnlockV8>
struct XMethodForwarder<T, 10,Sig, UnlockV8> : XMethodSignature<T,Sig>
  {
  typedef XMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (10 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;
    typedef typename sl::At< 7, XSignature<Sig> >::Type A7;
    typedef typename sl::At< 8, XSignature<Sig> >::Type A8;
    typedef typename sl::At< 9, XSignature<Sig> >::Type A9;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;
    typedef ArgCaster<A7> AC7;
    typedef ArgCaster<A8> AC8;
    typedef ArgCaster<A9> AC9;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
    AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));
    AC8 ac8; A8 arg8(ac8.ToNative(argv[8]));
    AC9 ac9; A9 arg9(ac9.ToNative(argv[9]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9 );
    }
  static XScriptValue Call( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative( self, func, argv ) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T  * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative(func, argv) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };

template <typename T, typename Sig, bool UnlockV8>
struct XMethodForwarderVoid<T, 10,Sig, UnlockV8> : XMethodSignature<T,Sig>
  {
  typedef XMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (10 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;
    typedef typename sl::At< 7, XSignature<Sig> >::Type A7;
    typedef typename sl::At< 8, XSignature<Sig> >::Type A8;
    typedef typename sl::At< 9, XSignature<Sig> >::Type A9;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;
    typedef ArgCaster<A7> AC7;
    typedef ArgCaster<A8> AC8;
    typedef ArgCaster<A9> AC9;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
    AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));
    AC8 ac8; A8 arg8(ac8.ToNative(argv[8]));
    AC9 ac9; A9 arg9(ac9.ToNative(argv[9]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9 );
    }
  static XScriptValue Call( T  & self, FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative( self, func, argv );
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T  * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative(func, argv);
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };
}
namespace Detail {
template <typename T, typename Sig, bool UnlockV8>
struct XConstMethodForwarder<T, 10,Sig, UnlockV8> : XConstMethodSignature<T,Sig>
  {
  typedef XConstMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (10 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;
    typedef typename sl::At< 7, XSignature<Sig> >::Type A7;
    typedef typename sl::At< 8, XSignature<Sig> >::Type A8;
    typedef typename sl::At< 9, XSignature<Sig> >::Type A9;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;
    typedef ArgCaster<A7> AC7;
    typedef ArgCaster<A8> AC8;
    typedef ArgCaster<A9> AC9;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
    AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));
    AC8 ac8; A8 arg8(ac8.ToNative(argv[8]));
    AC9 ac9; A9 arg9(ac9.ToNative(argv[9]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9 );
    }
  static XScriptValue Call( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative( self, func, argv ) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T const * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try { return CastToJS( CallNative(func, argv) ); }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };

template <typename T, typename Sig, bool UnlockV8>
struct XConstMethodForwarderVoid<T, 10,Sig, UnlockV8> : XConstMethodSignature<T,Sig>
  {
  typedef XConstMethodSignature<T,Sig> SignatureType;
  typedef char AssertArity[ (10 == sl::Arity<SignatureType>::Value) ? 1 : -1];
  typedef typename SignatureType::FunctionType FunctionType;
  typedef typename SignatureType::ReturnType ReturnType;
  static ReturnType CallNative( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
    typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
    typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
    typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
    typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
    typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
    typedef typename sl::At< 6, XSignature<Sig> >::Type A6;
    typedef typename sl::At< 7, XSignature<Sig> >::Type A7;
    typedef typename sl::At< 8, XSignature<Sig> >::Type A8;
    typedef typename sl::At< 9, XSignature<Sig> >::Type A9;

    typedef ArgCaster<A0> AC0;
    typedef ArgCaster<A1> AC1;
    typedef ArgCaster<A2> AC2;
    typedef ArgCaster<A3> AC3;
    typedef ArgCaster<A4> AC4;
    typedef ArgCaster<A5> AC5;
    typedef ArgCaster<A6> AC6;
    typedef ArgCaster<A7> AC7;
    typedef ArgCaster<A8> AC8;
    typedef ArgCaster<A9> AC9;

    AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
    AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
    AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
    AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
    AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
    AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
    AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
    AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));
    AC8 ac8; A8 arg8(ac8.ToNative(argv[8]));
    AC9 ac9; A9 arg9(ac9.ToNative(argv[9]));

    V8Unlocker<UnlockV8> const & unlocker( V8Unlocker<UnlockV8>() );
    return (ReturnType)(self.*func)(  arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9 );
    }
  static XScriptValue Call( T const & self, FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative( self, func, argv );
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  static ReturnType CallNative( FunctionType func, XScriptArguments const & argv )
    {
    T const * self = CastFromJS<T>(argv.This());
    if( ! self ) throw MissingThisExceptionT<T>();
    return (ReturnType)CallNative(*self, func, argv);
    }
  static XScriptValue Call( FunctionType func, XScriptArguments const & argv )
    {
    try
    {
    CallNative(func, argv);
    return v8::Undefined();
    }
    HANDLE_PROPAGATE_EXCEPTION;
    }
  };
}
//! Specialization for 10-arity calls.
template <>
struct CallForwarder<10>
  {
  template < typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
  static XScriptValue Call( XScriptObject const & self,
                            XScriptFunction const & func,
                            A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
                            )
    {
    XScriptValue args[] = {
      CastToJS(a0), CastToJS(a1), CastToJS(a2), CastToJS(a3), CastToJS(a4), CastToJS(a5), CastToJS(a6), CastToJS(a7), CastToJS(a8), CastToJS(a9)
    };
    return (self.IsEmpty() || func.IsEmpty())
        ? Toss("Illegal argument: empty v8::Handle<>.")
        : func->Call(self, sizeof(args)/sizeof(args[0]), args);
    }
  template < typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
  static XScriptValue Call( XScriptFunction const & func,
                            A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9
                            )
    {
    return Call( func, func, a0,a1,a2,a3,a4,a5,a6,a7,a8,a9 );
    }

  };
namespace Detail {
template <typename Sig>
struct CtorForwarderProxy<Sig,10>
  {
  enum { Arity = 10 };
  typedef typename XSignature<Sig>::ReturnType ReturnType;
  static ReturnType Call( XScriptArguments const & argv )
    {
    if( argv.Length() < Arity )
      {
      throw std::range_error("CtorForwarder<T,10>::Ctor() expects at least 10 JS arguments!");
      }
    else
      {
      typedef typename sl::At< 0, XSignature<Sig> >::Type A0;
      typedef typename sl::At< 1, XSignature<Sig> >::Type A1;
      typedef typename sl::At< 2, XSignature<Sig> >::Type A2;
      typedef typename sl::At< 3, XSignature<Sig> >::Type A3;
      typedef typename sl::At< 4, XSignature<Sig> >::Type A4;
      typedef typename sl::At< 5, XSignature<Sig> >::Type A5;
      typedef typename sl::At< 6, XSignature<Sig> >::Type A6;
      typedef typename sl::At< 7, XSignature<Sig> >::Type A7;
      typedef typename sl::At< 8, XSignature<Sig> >::Type A8;
      typedef typename sl::At< 9, XSignature<Sig> >::Type A9;

      typedef ArgCaster<A0> AC0;
      typedef ArgCaster<A1> AC1;
      typedef ArgCaster<A2> AC2;
      typedef ArgCaster<A3> AC3;
      typedef ArgCaster<A4> AC4;
      typedef ArgCaster<A5> AC5;
      typedef ArgCaster<A6> AC6;
      typedef ArgCaster<A7> AC7;
      typedef ArgCaster<A8> AC8;
      typedef ArgCaster<A9> AC9;

      AC0 ac0; A0 arg0(ac0.ToNative(argv[0]));
      AC1 ac1; A1 arg1(ac1.ToNative(argv[1]));
      AC2 ac2; A2 arg2(ac2.ToNative(argv[2]));
      AC3 ac3; A3 arg3(ac3.ToNative(argv[3]));
      AC4 ac4; A4 arg4(ac4.ToNative(argv[4]));
      AC5 ac5; A5 arg5(ac5.ToNative(argv[5]));
      AC6 ac6; A6 arg6(ac6.ToNative(argv[6]));
      AC7 ac7; A7 arg7(ac7.ToNative(argv[7]));
      AC8 ac8; A8 arg8(ac8.ToNative(argv[8]));
      AC9 ac9; A9 arg9(ac9.ToNative(argv[9]));

      typedef typename XScriptTypeInfo<ReturnType>::Type Type;
      return new Type(  arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9 );
      }
    }
  };

}