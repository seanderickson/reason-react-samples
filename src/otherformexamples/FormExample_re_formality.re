// Form example using re-formality

let str = ReasonReact.string;

module FormExampleModule = {
  open Formality;

  type field = 
    | Email
    | Name
    | RememberMe;

  type state = {
    email: string,
    name: string,
    rememberMe: bool,
  };

  type message = string;

  module EmailField = {
    let update = (state, value) => {...state, email: value};

    let validator = {
      field: Email,
      strategy: Strategy.OnFirstSuccessOrFirstBlur,
      dependents: None,
      validate: ({email}) => {
        let emailRegex = [%bs.re {|/.*@.*\..+/|}];
        switch (email) {
          | "" => Error("required")
          | _ as value when !value->Js.Re.test(emailRegex) =>
            Error("Invalid format")
          | _ => Ok(Valid)
        };
      },
    };
  };

  module NameField = {
    let update = (state, value) => {...state, name: value};

    let validator = {
      field: Name,
      strategy: Strategy.OnFirstSuccessOrFirstBlur,
      dependents: None,
      validate: ({name}) => {
        let nameRegex = [%bs.re {|/^\w+\s\w+$/|}];
        switch (name) {
        | "" => Error("required")
        | _ as value when !value->Js.Re.test(nameRegex)=> Error("Name must be two words")
        | _ => Ok(Valid)
        };
      },
    };
  };

  module RememberMeField = {
    let update = (state, value) => {...state, rememberMe: value};
  };

  let validators = [EmailField.validator, NameField.validator];
};

module FormExampleContainer = Formality.Make(FormExampleModule);

let component = ReasonReact.statelessComponent(__MODULE__);

let make = _ => {
  ...component,
  render: _ =>
    <FormExampleContainer 
      initialState={email: "", name: "", rememberMe: false}
      onSubmit={(state, form) => {
        Js.log2("Submitted with", state);
        Js.Global.setTimeout(
          () => {
            form.notifyOnSuccess(None);
            form.reset->Js.Global.setTimeout(3000)->ignore;
          },
          500
        )
        ->ignore;
      }}>
      ...{form=>
        <form
          className="form"
          onSubmit={form.submit->Formality.Dom.preventDefault}>
          <label htmlFor="email">(str("Email: "))</label>
          <input id="email" type_="text"
            value={form.state.email}
            disabled={form.submitting}
            onBlur={_ => form.blur(Email)}
            onChange={ event=>
              form.change(
                Email,
                FormExampleModule.EmailField.update(
                  form.state,
                  event->ReactEvent.Form.target##value
                ),
              )
            }
            />
            { switch(Email->(form.result)) {
              | Some(Error(message)) =>
                <div className={Cn.make(["form-message", "failure"])}>
                  message->str
                </div>
              | Some(Ok(Valid)) => 
                <div className={Cn.make(["form-message","success"])}>
                  {j|✓|j}->str
                </div>
              | Some(Ok(NoValue))
              | None => ReasonReact.null
              }
            }
          <br />
          <label htmlFor="name">(str("Name: "))</label>
          <input id="name" type_="text"
            value={form.state.name}
            disabled={form.submitting}
            onBlur={_ => form.blur(Name)}
            onChange={ event=>
              form.change(
                Name,
                FormExampleModule.NameField.update(
                  form.state,
                  event->ReactEvent.Form.target##value
                ),
              )
            }
            />
            { switch(Name->(form.result)) {
              | Some(Error(message)) =>
                <div className={Cn.make(["form-message", "failure"])}>
                  message->str
                </div>
              | Some(Ok(Valid)) => 
                <div className={Cn.make(["form-message","success"])}>
                  {j|✓|j}->str
                </div>
              | Some(Ok(NoValue))
              | None => ReasonReact.null
              }
            }
          <br />
          <label htmlFor="form-remember">(str("Remember me: "))</label>
          <input id="form-remember" type_="checkbox"
            checked={form.state.rememberMe}
            disabled={form.submitting}
            onBlur={_=>form.blur(RememberMe)}
            onChange={ event=>
              form.change(
                RememberMe,
                FormExampleModule.RememberMeField.update(
                  form.state,
                  event->ReactEvent.Form.target##checked,
                ),
              )
            }
            />
          <br />
          <button disabled={form.submitting}>
            (form.submitting ? "Submitting..." : "Submit")->str
          </button>
          { switch(form.status) {
            | Submitted =>
              <div className="form-status success">
                {j|✓ Logged In|j}->str
              </div>
            | _ => ReasonReact.null
          }}           
        </form>
      }
  </FormExampleContainer>
};

