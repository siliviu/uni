Contents =
InputAlphabet
States
InitialState
FinalStates
Transitions.

InputAlphabet = label {label}.
States = state {state}.
InitialState = state.
FinalStates = state {state}.
Transitions = transition {transition}.
label = a | b | ... | z |
        A | B | ... | Z |
        0 | 1 | ... 9 | + | -.
state = label{label}.
transition = state state label.