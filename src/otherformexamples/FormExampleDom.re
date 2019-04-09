//open Common;
let str = ReasonReact.string;

// Example of Form handling using no state;
// that is, use the DOM to hold the form state, instead of a using a reducer 
// component that manages the state separately.
//
// NOTE: state won't be used for this example; just identifying the passed in 
// property as "state" here.

type state = {
  name: string,
  email: string,
  date_of_birth: string,
  // nameRef: ref(option(Dom.element))
};

let component = ReasonReact.statelessComponent("FormDom");

// NOTE: FormData 
// https://developer.mozilla.org/en-US/docs/Web/API/FormData
// - has not been implemented for reason react yet (nor in Belt);
// - it could be usefull for DOM form field value extraction and serializing;
// - it is possible to map external functions on the FormData obj, like so:
// module FormData = {
//   type t;
//   [@bs.new] external make: unit => t = "FormData";
//   [@bs.send] external set: (t, string, 'a) => Js.t('a) = "set";
// };


let make = (~initialState: state, _children) => {
  let handleSubmit = (event) => {
    ReactEvent.Synthetic.preventDefault(event);

    let domForm = ReactEvent.Form.target(event);

    // NOTE: HTML form validation API is not available, so this is not a thing:
    // if (ReactEvent.Form.checkValidity(event)) {
    //   Js.log("yay valid");
    // }
    // But we can use the "escape hatch" to just invoke the native APIs:
    let validity = [%bs.raw {| domForm.checkValidity() |}];
    Js.log2("form validity", validity);

    // The DOM tree may be traversed like so:
    Js.log(domForm##elements);
    Js.log2("name:", domForm##elements##name##value);

  };
  {
    ...component,
    render: _self =>
      <form noValidate=true onSubmit=( e=>handleSubmit(e)) >
        <label htmlFor="name" >(str("Name: "))</label>
        <input id="name" name="name" type_="text"
          required=true 
          // ref={handle(setNameRef)}
          defaultValue={initialState.name} />
        <label htmlFor="email">(str("Email: "))</label>
        <input id="email" name="email" type_="email" defaultValue={initialState.email} />
        <label htmlFor="date_of_birth">(str("Date of birth:"))</label>
        <input id="date_of_birth" name="date_of_birth" type_="date" defaultValue={initialState.date_of_birth} />
        <button type_="submit">(str("submit"))</button>
      </form>
  } 
}