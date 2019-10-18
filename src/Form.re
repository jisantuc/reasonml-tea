open Js.String;

type error =
  | PasswordTooShort
  | PasswordsDontMatch
  | NameTooShort;

type state = {
  name: string,
  password: string,
  passwordAgain: string,
  errors: list(error),
};

type action =
  | Name(string)
  | Password(string)
  | PasswordAgain(string);

let checkName: string => list(error) =
  name =>
    if (name->length < 5) {
      [];
    } else {
      [NameTooShort];
    };

let viewInput: (string, string, ReactEvent.Form.t => unit) => React.element =
  (inpType, placeholder, onInput) =>
    <input type_=inpType placeholder onInput />;

let showErr: error => string =
  err =>
    switch (err) {
    | NameTooShort => "Name too short."
    | PasswordTooShort => "Password too short."
    | PasswordsDontMatch => "Passwords don't match."
    };

let renderErrors: list(error) => React.element =
  errs => {
    let errStrings = List.map(showErr, errs);
    let errString: string = String.concat(" ", errStrings);
    if (errStrings != []) {
      <div style={ReactDOMRe.Style.make(~color="red", ())}>
        {ReasonReact.string(errString)}
      </div>;
    } else {
      <div style={ReactDOMRe.Style.make(~color="green", ())}>
        {ReasonReact.string("Ok!")}
      </div>;
    };
  };

let checkErrors: state => list(error) =
  state => {
    let nameErr =
      if (state.name->length < 5) {
        [NameTooShort];
      } else {
        [];
      };

    let passwordTooShortErr =
      if (state.password->length < 5) {
        [PasswordTooShort];
      } else {
        [];
      };

    let passwordsDontMatchErr =
      if (state.password != state.passwordAgain) {
        [PasswordsDontMatch];
      } else {
        [];
      };

    List.concat([nameErr, passwordTooShortErr, passwordsDontMatchErr]);
  };

let loggingId: 't => 't =
  t => {
    Js.log(t);
    t;
  };

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Name(s) =>
          let newState = {...state, name: s};
          {...newState, errors: checkErrors(newState)};
        | Password(s) =>
          let newState = {...state, password: s};
          {...newState, errors: checkErrors(newState)};
        | PasswordAgain(s) =>
          let newState = {...state, passwordAgain: s};
          {...newState, errors: checkErrors(newState)};
        },
      {name: "", password: "", passwordAgain: "", errors: []},
    );

  <div>
    <h2> {ReasonReact.string("A form!")} </h2>
    <div>
      {
        viewInput("text", "name", _event =>
          dispatch(Name(_event->ReactEvent.Form.target##value))
        )
      }
      <br />
      {
        viewInput("password", "password", _event =>
          dispatch(Password(_event->ReactEvent.Form.target##value))
        )
      }
      <br />
      {
        viewInput("password", "password again", _event =>
          dispatch(PasswordAgain(_event->ReactEvent.Form.target##value))
        )
      }
    </div>
    {renderErrors(state.errors)}
  </div>;
};
