open Common

type formField = 
  | Name
  | Channels
  | Mag;

type action =
  | UpdateValue(formField, string);

let component = ReasonReact.reducerComponent("MsForm");

let getValue = event => ReactEvent.Form.target(event)##value;

let make = (~initialState: microscopeState, ~handleSubmit, _children )=> {
  ...component,
  initialState: () => {
    Js.log2("initialState: ", initialState);
    initialState;
  },
  reducer: (action, state) => {
    let update = (formField, value, state) =>
      switch(formField) {
        | Name => {...state, name: value}
        | Channels => {...state, channels: value }
        | Mag => { ...state, magnification: value }
      };
    switch(action){
      | UpdateValue(field, value) => {
        ReasonReact.Update(update(field, value, state));
      }
    }
  },
  render: self => {
    let handleChange = (field, value) => self.send(UpdateValue(field, value));
    let formSubmit = (event) => {
      ReactEvent.Form.preventDefault(event);
      handleSubmit(self.state);
    };
    <form className="form" onSubmit=(e=>formSubmit(e)) >
      <label htmlFor="name">(str("Name"))</label>
      <input id="name" value={self.state.name} 
        onChange={ event=> getValue(event) |> handleChange(Name) }
      />
      <label htmlFor="channels">(str("Channels:"))</label>
      <input id="channels" value={self.state.channels} 
        onChange={ event=> getValue(event) |> handleChange(Channels) }
      />
      <label htmlFor="mag" >(str("Magnification:"))</label>
      <input id="mag" value={self.state.magnification} 
        onChange={ event=> getValue(event) |> handleChange(Mag) }
      />
      <button type_="submit" >(str("submit"))</button>
    </form>
  }
}