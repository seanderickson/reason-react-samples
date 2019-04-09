open Common;


// let states: list(state) = [
//   { name: "Jill", email: "jill@email.com", date_of_birth: "1969-09-17"},
//   { name: "Mary", email: "mary@email.com", date_of_birth: "1980-04-01"},
//   { name: "Jill", email: "jill@email.com", date_of_birth: "1990-01-01"},
// ];

// let renderForRoute = (element) =>
//   ReactDOMRe.renderToElementWithId(element, "app");

// let showMainPage = () => {
//   ReactDOMRe.renderToElementWithId(
//     <FormExampleDom initialState=List.nth(states,0) />,
//     "app"
//   );
// };

// let showNotFoundPage = (_path) => {
//   Js.log2("not found", _path);
//   ReactDOMRe.renderToElementWithId(
//     <div>
//       (str("not found: " ++ 
//         (_path |> List.fold_left(
//           (a,b) => a ++ "/" ++ b,
//           ""
//       ))))
//     </div>,
//     "app"
//   );
// };

// let watcherID = ReasonReact.Router.watchUrl(url => {
//   switch (url.path) {
//   | ["1"] => {
//     renderForRoute(<FormExampleDom initialState=List.nth(states,0)/>)
//   } 
//   | ["2"] => {
//     renderForRoute(<FormExampleDom initialState=List.nth(states,1)/>)
//   } 
//   | ["3"] => {
//     renderForRoute(<FormExampleDom initialState=List.nth(states,2)/>)
//   } 
//   | [] => showMainPage()
//   | _ => showNotFoundPage(url.path)
//   }
// });



ReactDOMRe.renderToElementWithId(
    // <div className="wrapper">
    <RouterExample />,
    // </div>,
  "app");