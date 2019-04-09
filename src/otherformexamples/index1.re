[%bs.raw {|require('./simpleForm1.css')|}];


ReactDOMRe.renderToElementWithId(
  <div>
    (ReasonReact.string("Test Form: re-formality:"))
    <FormExample_re_formality />
    <br />
    (ReasonReact.string("Test Form: reform:"))
    <FormExample_reform />
    <br />
    (ReasonReact.string("Test Form: DOM:"))
    <FormExampleDom
      initialState={ 
        name: "Joe",
        email: "joe@email.com",
        date_of_birth: "1980-11-11"
      }
    />
    <br />
    (ReasonReact.string("Date Picker test"))
    <DatePickerExample />    
  </div>,
  "app",
);


