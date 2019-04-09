
type projectState = {
  projectName: string,
  pi: string,
  primaryIrb: string,
  lspIrb: string,
  protocolIo: string,
  scientistFrom: string,
  pathologyCore: string,
  coPi: string,
  scientistConducting: string,
  grant: string,
  purpose: string,
  organism: string,
  sampleSize: string,
  cycles: string,
  comments: string
};

type microscopeState = {
  name: string,
  channels: string,
  magnification: string,
};

type route = 
  | Project
  | Microscope;
  // | Samples
  // | Planned
  // | Actual;

type routerState = {
  route,
  projectState,
  microscopeState
};



let str = ReasonReact.string;
