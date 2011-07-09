/* $Id: simplemenu.css.tpl,v 1.1.2.2 2010/06/07 22:35:44 alexiswilke Exp $ */

/* There is a version of this file commented in great detail for educational purposes here:
 * http://users.tpg.com.au/j_birch/plugins/superfish/superfish.commented.css
 */

@STICKY_TABLE@

/*** ESSENTIAL STYLES ***/
#simplemenu, #simplemenu * {
  margin: 0;
  padding: 0;
  list-style: none;
}

#simplemenu {
  line-height: 1.0;
  @FIX@
  @MENUBAR_ZINDEX@
}

#simplemenu ul {
  position: absolute;
  top: -999em;
  width: 14em;
  font-size: 1em;
  line-height: 1em;
}

#simplemenu ul li,
#simplemenu a {
  width: 100%;
}

#simplemenu li {
  float: left;
  position: relative;
}

#simplemenu a {
  display: block;
}

#simplemenu li ul {
  @DROPDOWN_ZINDEX@
}

#simplemenu li:hover ul,
ul#simplemenu li.sfHover ul {
  left: 0px;
  top: 21px;
}

#simplemenu li:hover li ul,
#simplemenu li.sfHover li ul {
  top: -999em;
}

#simplemenu li li:hover ul,
ul#simplemenu li li.sfHover ul {
  left: 14em;
  top: -1px;
}

.superfish li:hover ul,
.superfish li li:hover ul {
  top: -999em;
}

/* vim: ts=2 sw=2 et syntax=css
*/
