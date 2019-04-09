// Form example using reform

let str = ReasonReact.string;

module Form1Params = {
  
  type state = {
    name: string,
    email: string
  };

  type fields = [ | `email | `name ];

  let lens = [
    (`email, s=> s.email, (s, email) => {...s, email}),
    (`name, s=> s.name, (s, name) => {...s, name})
  ];
};

module Form1Form = ReForm.Create(Form1Params);

let component = ReasonReact.statelessComponent("Form1-reform");

let nameRegex = [%bs.re {|/^\w+\s\w+$/|}];
let make = _children => {
  ...component,
  render: _self => 
    <Form1Form
      onSubmit=(({values}) => Js.log(values))
      initialState={email: "", name: ""}
      schema=[
        (`email, Email), 
        (`name, Custom(values=> 
          switch(values.name) {
            | "" => Some("Required")
            | _ as value when !value->Js.Re.test(nameRegex)=> Some("Name must be two words")
            | _ => None} ) )]
    >
      ...(
        ({handleSubmit, handleChange, form, getErrorForField}) =>
          <form
            onSubmit=(ReForm.Helpers.handleDomFormSubmit(handleSubmit))>
            <label htmlFor="email" >(str("Email"))</label>
              <input id="email" value=form.values.email
                onChange=(
                  ReForm.Helpers.handleDomFormChange(handleChange(`email))
                )
              />
            <p>
              (
                getErrorForField(`email)
                |> Belt.Option.getWithDefault(_, "")
                |> str
              )
            </p>
            <label htmlFor="name" >(str("Name"))</label>
              <input id="name" value=form.values.name
                onChange=(
                  ReForm.Helpers.handleDomFormChange(handleChange(`name))
                )
              />
            <p>
              (
                getErrorForField(`name)
                |> Belt.Option.getWithDefault(_, "")
                |> str
              )
            </p>
            <button type_="submit">
              ("Submit" |> str)
            </button>
          </form>

      )
    </Form1Form>
}