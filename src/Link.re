let component = ReasonReact.statelessComponent("Link");

let handleClick = (href, event) =>
  if (! ReactEvent.Mouse.defaultPrevented(event)) {
    ReactEvent.Mouse.preventDefault(event);
    ReasonReact.Router.push(href)
  };

let make = (~href, ~selected, children) => {
  ...component,
  render: (_self) => {
    <a href={href} className=( selected?"selected":"") onClick=handleClick(href)  >...children</a>
  }
};