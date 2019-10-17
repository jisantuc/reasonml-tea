open Js.String;

type state = {
    message: string
};

[@react.component]
let make = () => {
    let (state, setState) = React.useState(() => "");

    <div>
      <input type_="text" onInput={_event => setState(_event->ReactEvent.Form.target##value)}/>
      <div>{ ReasonReact.string("Little bit louder now: " ++ state->toUpperCase)} </div>
    </div>;
};