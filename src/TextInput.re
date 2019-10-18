open Js.String;

type state = {message: string};

[@react.component]
let make = () => {
  let (state, setState) = React.useState(() => "");

  <div>
    <h2> {ReasonReact.string("A text input!")} </h2>
    <div>
      <input
        type_="text"
        onInput={_event => setState(_event->ReactEvent.Form.target##value)}
      />
      <div>
        {ReasonReact.string("Little bit louder now: " ++ state->toUpperCase)}
      </div>
    </div>
  </div>;
};
