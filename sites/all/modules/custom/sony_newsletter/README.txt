Sony Newsletter Module

This module serves to provide a unified newsletter form management interface for
the multisite platform.  This was pretty easily managed before sites became 
global.  Also with the advent of the lyris module and possibly other integration
points, not all subscription forms will be in nodes.

What it does:
- provides a menu callback for /newsletter
- provides a localizable newsletter configuration for each enabled locale
- each configuration contains
  - title
  - body
  - path
  - path alias
- The newsletter page will either redirect to the specified path or display the 
  body.  The path takes precedence.
- The translation interface should be as similar as possible to the node
  translation interface, so users feel comfortable using it.
- The editing interface should be as simple and stripped down as possible
- Additional integration
  - There should be integration to directly display forms provided by other 
    modules like lyris.  Maybe just a list of supported forms that can be 
    displayed.