// let str = ReasonReact.string;

/* ReactJS used by ReasonReact */
/* This component wraps a ReactJS one, so that ReasonReact components can consume it */
/* Typing the myBanner.js component's output as a `reactClass`. */
// [@bs.module] external datepicker : ReasonReact.reactClass = "@y0c/react-datepicker/lib/components/DatePicker.js";


// If JS component uses ES6 default export (export default MyComponent) (or, you forgot to export the component altogether!).
// and You're using Babel/Webpack to compile those ES6 modules.
// see https://github.com/reasonml/reason-react/blob/master/docs/element-type-is-invalid.md
[@bs.module "@y0c/react-datepicker/lib/components/DatePicker.js"] external datepicker: ReasonReact.reactClass = "default";


// [%bs.raw {|require('./node_modules/@y0c/react-datepicker/assets/styles/calendar.scss')|}];
[%bs.raw {|require('@y0c/react-datepicker/assets/styles/calendar.scss')|}];

[%bs.raw {|require('moment/locale/en-ca.js')|}];


[@bs.deriving abstract]
type jsProps = {
  local: string,
  onChange: (string) => string
};

/* This is like declaring a normal ReasonReact component's `make` function, except the body is a the interop hook wrapJsForReason */
let make = (children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=datepicker,
    ~props=jsProps(~local="en-ca"),
    children,
  );

