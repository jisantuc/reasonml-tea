type state = {
    count: int
};

type action = 
  | Increment
  | Decrement;

[@react.component]
let make = () => {
    let (state, dispatch) = React.useReducer((state, action) =>
        switch (action) {
        | Increment => { count: state.count + 1 }
        | Decrement => { count: state.count - 1 }
        }, {count: 0});

    let message = "Current value: " ++ string_of_int(state.count);

    <div>
      <button onClick={_event => dispatch(Decrement)}>
        {ReasonReact.string("-")}
      </button>
      { ReasonReact.string(message) }
      <button onClick={_event => dispatch(Increment)}>
        {ReasonReact.string("+")}
      </button>
    </div>;
};