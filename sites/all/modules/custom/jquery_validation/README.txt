




Available rules and paramters
========================================
required => boolean
  Basic required validation. Return false if the element is empty (text input) 
  or unchecked (radio/checkbxo) or nothing selected (select).
   
minlength => integer
maxlength => integer
rangelength => array(integer min, integer max)
  Return false, if the element is:
  - some kind of text input and its length is too short or too long
  - a set of checkboxes has not enough or too many boxes checked
  - a select and has not enough or too many options selected 
  
min => integer value
max => integer value
range => array(integer min, integer max)
  Works with text inputs to validate minimum and maximum values.
  
email => boolean
  Require a valid email address.
  
url => boolean 
  Require a valid URL.

date => boolean
  Require a valid date.  Uses JavaScripts built-in Date to test if the date is 
  valid, and does therefore no sanity checks. Only the format must be valid, 
  not the actual date, eg 30/30/2008 is a valid date. Works with text inputs.

dateISO => boolean
  Makes the element require a ISO date.
  
dateDE => boolean
  Makes the element require a german date.
  
number => boolean
  Makes the element require a decimal number.

numberDE => boolean
  Makes the element require a decimal number with german format.

digits => boolean
  Makes the element require digits only.

creditcard => boolean
  Makes the element require a creditcard number.

accept => string
  Makes the element require a certain file extension.  If nothing is specified, 
  only images are allowed (png, jpeg, gif). Extensions should be in
  pipe-delimited format, like png|jpg|gif.

equalTo => string
  Requires the element to be the same as another one. Specify a jquery selector
  of the element to match against.