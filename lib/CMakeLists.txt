
add_library(YYTK STATIC
        "YYToolkit/YYToolkit/source/YYTK/Shared/YYTK_Shared_Types.cpp"
        "YYToolkit/YYToolkit/source/YYTK/Module Interface/Interface.cpp"
        "YYToolkit/YYToolkit/source/YYTK/Module Internals/Console/Console.cpp"
        "YYToolkit/YYToolkit/source/YYTK/Module Internals/Hooks/Hooks.cpp"
        "YYToolkit/YYToolkit/source/YYTK/Module Internals/GameMaker/Generic/Generic.cpp"
        "YYToolkit/YYToolkit/source/YYTK/Module Internals/GameMaker/Generic/Generic-RunnerInterfaceNew.cpp"
        "YYToolkit/YYToolkit/source/YYTK/Module Internals/GameMaker/Generic/Generic-Rooms.cpp"
        "YYToolkit/YYToolkit/source/YYTK/Module Internals/GameMaker/Generic/Generic-Objects.cpp"
        "YYToolkit/YYToolkit/source/YYTK/Module Internals/GameMaker/Generic/Generic-CodeExecute.cpp"
        "YYToolkit/YYToolkit/source/YYTK/Module Internals/GameMaker/YYC/YYC-Rooms.cpp"
        "YYToolkit/YYToolkit/source/YYTK/Module Internals/GameMaker/YYC/YYC-Functions.cpp"
        "YYToolkit/YYToolkit/source/YYTK/Module Internals/GameMaker/YYC/YYC-BuiltinVariables.cpp"
        "YYToolkit/YYToolkit/source/YYTK/Module Internals/GameMaker/YYC/YYC-Arrays.cpp"
        "YYToolkit/YYToolkit/source/YYTK/Module Internals/GameMaker/VM/VM-Rooms.cpp"
        "YYToolkit/YYToolkit/source/YYTK/Module Internals/GameMaker/VM/VM-Functions.cpp"
        "YYToolkit/YYToolkit/source/YYTK/Module Internals/GameMaker/VM/VM-BuiltinVariables.cpp"
        "YYToolkit/YYToolkit/source/YYTK/Module Internals/GameMaker/VM/VM-Arrays.cpp"
)

target_include_directories(YYTK PUBLIC
        "YYToolkit/YYToolkit/include"
)
