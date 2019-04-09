open Common;

type formField = 
  | ProjectName
  | PI
  | PrimaryIrb
  | LspIrb
  | ProtocolIo
  | ScientistFrom
  | PathologyCore
  | CoPi
  | ScientistConducting
  | Grant
  | Purpose
  | Organism
  | SampleSize
  | Cycles
  | Comments;

type action =
  | UpdateValue(formField, string);

let component = ReasonReact.reducerComponent("ProjectForm");

let getValue = event => ReactEvent.Form.target(event)##value;

let make = (~initialState: projectState, ~handleSubmit, _children )=> {
  ...component,
  initialState: () => {
    Js.log2("initialState: ", initialState);
    initialState;
  },
  reducer: (action, state) => {
    let update = (formField, value, state) =>
      switch(formField) {
        | ProjectName => {...state, projectName: value}
        | PI => {...state, pi: value}
        | PrimaryIrb => {...state, primaryIrb: value}
        | LspIrb => { ...state, lspIrb: value}
        | ProtocolIo => {...state, protocolIo: value}
        | ScientistFrom => {...state, scientistFrom: value}
        | PathologyCore => {...state, pathologyCore: value}
        | CoPi => {...state, 
            coPi: switch(value) {
              | "" => None
              | _ => Some(value)
            }}
        | ScientistConducting => {...state, scientistConducting: value}
        | Grant => {...state, grant: value}
        | Purpose => {...state, purpose: value}
        | Organism => {...state, organism: value}
        | SampleSize => {...state, 
          sampleSize: switch(value) {
            | "" => None
            | _ => Some(int_of_string(value))
          }}
        | Cycles => {...state, cycles: value}
        | Comments => {...state, comments: value}
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
      <input id="name" value={self.state.projectName} required=true
        onChange={ event=> getValue(event) |> handleChange(ProjectName) }
      />
      <label htmlFor="pi">(str("PI:"))</label>
      <input id="pi" value={self.state.pi} 
        onChange={ event=> getValue(event) |> handleChange(PI) }
      />
      <label htmlFor="scientistFrom" >(str("Scientist samples received from:"))</label>
      <input id="scientistFrom" value={self.state.scientistFrom} 
        onChange={ event=> getValue(event) |> handleChange(ScientistFrom) }
      />
      <label htmlFor="primaryIrb" >(str("Primary IRB:"))</label>
      <input id="primaryIrb" value={self.state.primaryIrb} 
        onChange={ event=> getValue(event) |> handleChange(PrimaryIrb) }
      />
      <label htmlFor="lspIrb" >(str("LSP IRB:"))</label>
      <input id="lspIrb" value={self.state.lspIrb} 
        onChange={ event=> getValue(event) |> handleChange(LspIrb) }
      />
      <label htmlFor="protocolIo" >(str("Protocol.io:"))</label>
      <input id="protocolIo" value={self.state.protocolIo} 
        onChange={ event=> getValue(event) |> handleChange(ProtocolIo) }
      />
      <label htmlFor="pathologyCore" >(str("Pathology Core:"))</label>
      <input id="pathologyCore" value={self.state.pathologyCore} 
        onChange={ event=> getValue(event) |> handleChange(PathologyCore) }
      />
      <label htmlFor="coPi" >(str("Internal LSP coPI/Primary contact:"))</label>
      <input id="coPi" value={
        switch(self.state.coPi) {
          | Some(value) => value
          | None => ""
        }} 
        onChange={ event=> getValue(event) |> handleChange(CoPi) }
      />
      <label htmlFor="scientistConducting" >(str("Scientist conducting CyCIF experiment:"))</label>
      <input id="scientistConducting" value={self.state.scientistConducting} 
        onChange={ event=> getValue(event) |> handleChange(ScientistConducting) }
      />
      <label htmlFor="grant" >(str("Grant:"))</label>
      <input id="grant" value={self.state.grant} 
        onChange={ event=> getValue(event) |> handleChange(Grant) }
      />
      <label htmlFor="purpose" >(str("Purpose:"))</label>
      <input id="purpose" value={self.state.purpose} 
        onChange={ event=> getValue(event) |> handleChange(Purpose) }
      />
      <label htmlFor="organism" >(str("Organism:"))</label>
      <input id="organism" value={self.state.organism} 
        onChange={ event=> getValue(event) |> handleChange(Organism) }
      />
      <label htmlFor="sampleSize" >(str("Sample Size:"))</label>
      <input id="sampleSize" value={
        switch(self.state.sampleSize) {
          | Some(value) => string_of_int(value)
          | None => ""
        }} 
        onChange={ event=> getValue(event) |> handleChange(SampleSize) }
      />
      <label htmlFor="cycles" >(str("Cycles:"))</label>
      <input id="cycles" value={self.state.cycles} 
        onChange={ event=> getValue(event) |> handleChange(Cycles) }
      />
      <label htmlFor="comments" >(str("Comments:"))</label>
      <input id="comments" value={self.state.comments} 
        onChange={ event=> getValue(event) |> handleChange(Comments) }
      />
      <button type_="submit" >(str("submit"))</button>
    </form>
  }
}