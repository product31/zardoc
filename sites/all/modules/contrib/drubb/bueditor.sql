-- phpMyAdmin SQL Dump
-- version 2.10.2
-- http://www.phpmyadmin.net
-- 
-- Host: localhost
-- Generation Time: May 29, 2009 at 02:15 PM
-- Server version: 5.0.41
-- PHP Version: 5.2.5

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

-- 
-- Database: `drubb`
-- 

-- 
-- Dumping data for table `bueditor_buttons`
-- 

REPLACE INTO `bueditor_buttons` VALUES (1, 1, 'Insert/edit image', 'php:\n$imce_url = function_exists(''imce_access'') && imce_access() ? url(''imce'') : '''';\n\nreturn "js:\nvar B = eDefBrowseButton(''$imce_url'', ''attr_src'', ''Browse'', ''image'');\nvar form = [\n {name: ''src'', title: ''Image URL'', suffix: B},\n {name: ''width'', title: ''Width x Height'', suffix: '' x '', getnext: true, attributes: {size: 3}},\n {name: ''height'', attributes: {size: 3}},\n {name: ''alt'', title: ''Alternative text''}\n];\neDefTagDialog(''img'', form, ''Insert/edit image'', ''OK'');\n";', 'image.png', 'M', -10);
REPLACE INTO `bueditor_buttons` VALUES (2, 1, 'Insert/edit link', 'php:\n$imce_url = function_exists(''imce_access'') && imce_access() ? url(''imce'') : '''';\n\nreturn "js:\nvar B = eDefBrowseButton(''$imce_url'', ''attr_href'', ''Browse'', ''link'');\nvar form = [\n {name: ''href'', title: ''Link URL'', suffix: B},\n {name: ''html'', title: ''Link text''},\n {name: ''title'', title: ''Link title''}\n];\neDefTagDialog(''a'', form, ''Insert/edit link'', ''OK'');\n";', 'link.png', 'L', -10);
REPLACE INTO `bueditor_buttons` VALUES (23, 2, 'Code', '[code]%TEXT%[/code]', 'Code', 'C', 0);
REPLACE INTO `bueditor_buttons` VALUES (4, 1, 'Bold', '<strong>%TEXT%</strong>', 'bold.png', 'B', -6);
REPLACE INTO `bueditor_buttons` VALUES (5, 1, 'Italic', 'js: eDefTagger(''em'');/*toggle tag*/', 'italic.png', 'I', -6);
REPLACE INTO `bueditor_buttons` VALUES (6, 1, 'Headers', 'js: eDefTagChooser([\n [''h1'', ''Header1''],\n [''h2'', ''Header2''],\n [''h3'', ''Header3''],\n [''h4'', ''Header4'']\n], true, ''li'', ''ul'', ''slideDown'');/*choose among tags*/', 'headers.png', 'H', -5);
REPLACE INTO `bueditor_buttons` VALUES (8, 1, 'Ordered list. Converts selected lines to a numbered list.', 'js: eDefTagLines(''<ol>\\n'', '' <li>'', ''</li>'', ''\\n</ol>'');', 'ol.png', 'O', -2);
REPLACE INTO `bueditor_buttons` VALUES (9, 1, 'Unordered list. Converts selected lines to a bulleted list.', 'js: eDefTagLines(''<ul>\\n'', '' <li>'', ''</li>'', ''\\n</ul>'');', 'ul.png', 'U', -2);
REPLACE INTO `bueditor_buttons` VALUES (22, 2, 'Quote', '[quote]%TEXT%[/quote]', 'Quote', 'Q', -1);
REPLACE INTO `bueditor_buttons` VALUES (11, 1, 'Teaser break', '<!--break-->', 'teaserbr.png', 'T', 2);
REPLACE INTO `bueditor_buttons` VALUES (12, 1, 'Preview', 'js: eDefPreview();', 'preview.png', 'P', 6);
REPLACE INTO `bueditor_buttons` VALUES (13, 1, 'Help', 'js: eDefHelp(''slideDown'');', 'help.png', 'F', 10);
REPLACE INTO `bueditor_buttons` VALUES (14, 2, 'Insert/edit image', 'js:\nvar M = E.getSelection().match(new RegExp(''^\\\\[img(?:=(\\\\d+)x(\\\\d+))?](.+)\\\\[/img]$'')) || ['''', '''', '''', ''''];\nvar form = [\n {name: ''src'', title: ''URL'', value: M[3], suffix: eDefBrowseButton(''/?q=imce'', ''attr_src'', ''Browse'', ''image'')},\n {name: ''width'', value: M[1]},\n {name: ''height'', value: M[2]}\n];\neDefTagDialog(''img'', form, ''Insert/edit image'', ''OK'', ''bbcImgProcess'');\n\nbbcImgProcess = function(tag, form) {\n  var src = form.elements[''attr_src''].value;\n  var width = form.elements[''attr_width''].value;\n  var height = form.elements[''attr_height''].value;\n  var str = ''[img''+ (width ? (''=''+ width +''x''+ height) : '''') +'']''+ src +''[/img]'';\n  editor.dialog.close();\n  if (src) editor.active.replaceSelection(str);\n}', 'image.png', 'M', -10);
REPLACE INTO `bueditor_buttons` VALUES (15, 2, 'Insert/edit link', 'js:\nvar S = E.getSelection();\nvar M = S.match(new RegExp(''^\\\\[url(?:=([^\\\\]]*))?]((?:.|[\\r\\n])*)\\\\[/url]$'')) || ['''', '''', ''''];\nvar form = [\n {name: ''href'', title: ''URL'', value: M[1] ? M[1] : M[2], suffix: eDefBrowseButton(''/?q=imce'', ''attr_href'', ''Browse'', ''link'')},\n {name: ''text'', value: M[1] ? M[2] : (M[0] ? '''' : S)}\n];\neDefTagDialog(''a'', form, ''Insert/edit link'', ''OK'', ''bbcUrlProcess'');\n\nbbcUrlProcess = function(tag, form) {\n  var url = form.elements[''attr_href''].value;\n  var text = form.elements[''attr_text''].value;\n  var str = ''[url''+ (text ? (''=''+ url) : '''') +'']''+ (text ? text : url) +''[/url]'';\n  editor.dialog.close();\n  if (url) editor.active.replaceSelection(str);\n}', 'link.png', 'L', -10);
REPLACE INTO `bueditor_buttons` VALUES (16, 2, 'Bold', '[b]%TEXT%[/b]', 'bold.png', 'B', -6);
REPLACE INTO `bueditor_buttons` VALUES (17, 2, 'Italic', '[i]%TEXT%[/i]', 'italic.png', 'I', -6);
REPLACE INTO `bueditor_buttons` VALUES (18, 2, 'Ordered list. Converts selected lines to a numbered list.', 'js: eDefSelProcessLines(''[list=1]\\n'', '' [*]'', '''', ''\\n[/list]'');', 'ol.png', 'O', -2);
REPLACE INTO `bueditor_buttons` VALUES (19, 2, 'Unordered list. Converts selected lines to a bulleted list.', 'js: eDefSelProcessLines(''[list]\\n'', '' [*]'', '''', ''\\n[/list]'');', 'ul.png', 'U', -2);
REPLACE INTO `bueditor_buttons` VALUES (20, 2, 'Preview', 'js:\nfunction BBC2HTML(S) {\nif (S.indexOf(''['') < 0) return S;\n\nfunction X(p, f) {return new RegExp(p, f)}\nfunction D(s) {return rD.exec(s)}\nfunction R(s) {return s.replace(rB, P)}\nfunction A(s, p) {for (var i in p) s = s.replace(X(i, ''g''), p[i]); return s;}\n\nfunction P($0, $1, $2, $3) {\n  if ($3 && $3.indexOf(''['') > -1) $3 = R($3);\n  switch ($1) {\n    case ''url'':case ''anchor'':case ''email'': return ''<a ''+ L[$1] + ($2||$3) +''">''+ $3 +''</a>'';\n    case ''img'': var d = D($2); return ''<img src="''+ $3 +''"''+ (d ? '' width="''+ d[1] +''" height="''+ d[2] +''"'' : '''') +'' alt="''+ (d ? '''' : $2) +''" />'';\n    case ''flash'':case ''youtube'': var d = D($2)||[0, 425, 366]; return ''<object type="application/x-shockwave-flash" data="''+ Y[$1] + $3 +''" width="''+ d[1] +''" height="''+ d[2] +''"><param name="movie" value="''+ Y[$1] + $3 +''" /></object>'';\n    case ''float'': return ''<span style="float: ''+ $2 +''">''+ $3 +''</span>'';\n    case ''left'':case ''right'':case ''center'':case ''justify'': return ''<div style="text-align: ''+ $1 +''">''+ $3 +''</div>'';\n    case ''google'':case ''wikipedia'': return ''<a href="''+ G[$1] + $3 +''">''+ $3 +''</a>'';\n    case ''b'':case ''i'':case ''u'':case ''s'':case ''sup'':case ''sub'':case ''h1'':case ''h2'':case ''h3'':case ''h4'':case ''h5'':case ''h6'':case ''table'':case ''tr'':case ''th'':case ''td'': return ''<''+ $1 +''>''+ $3 +''</''+ $1 +''>'';\n    case ''row'': case ''r'':case ''header'':case ''head'':case ''h'':case ''col'':case ''c'': return ''<''+ T[$1] +''>''+ $3 +''</''+ T[$1] +''>'';\n    case ''acronym'':case ''abbr'': return ''<''+ $1 +'' title="''+ $2 +''">''+ $3 +''</''+ $1 +''>'';\n  }\n  return ''[''+ $1 + ($2 ? ''=''+ $2 : '''') +'']''+ $3 +''[/''+ $1 +'']'';\n}\n\nvar rB = X(''\\\\[([a-z][a-z0-9]*)(?:=([^\\\\]]+))?]((?:.|[\\r\\n])*?)\\\\[/\\\\1]'', ''g''), rD = X(''^(\\\\d+)x(\\\\d+)$'');\nvar L = {url: ''href="'', ''anchor'': ''name="'', email: ''href="mailto: ''};\nvar G = {google: ''http://www.google.com/search?q='', wikipedia: ''http://www.wikipedia.org/wiki/''};\nvar Y = {youtube: ''http://www.youtube.com/v/'', flash: ''''};\nvar T = {row: ''tr'', r: ''tr'', header: ''th'', head: ''th'', h: ''th'', col: ''td'', c: ''td''};\nvar C = {notag: [{''\\\\['': ''&#91;'', '']'': ''&#93;''}, '''', ''''], code: [{''<'': ''&lt;''}, ''<code><pre>'', ''</pre></code>'']};\nC.php = [C.code[0], C.code[1]+ ''&lt;?php '', ''?>''+ C.code[2]];\nvar F = {font: ''font-family:$1'', size: ''font-size:$1px'', color: ''color:$1''};\nvar U = {c: ''circle'', d: ''disc'', s: ''square'', ''1'': ''decimal'', a: ''lower-alpha'', A: ''upper-alpha'', i: ''lower-roman'', I: ''upper-roman''};\nvar I = {}, B = {};\n\nfor (var i in C) I[''\\\\[(''+ i +'')]((?:.|[\\r\\n])*?)\\\\[/\\\\1]''] = function($0, $1, $2) {return C[$1][1] + A($2, C[$1][0]) + C[$1][2]};\nfor (var i in F) {B[''\\\\[''+ i +''=([^\\\\]]+)]''] = ''<span style="''+ F[i] +''">''; B[''\\\\[/''+ i +'']''] = ''</span>'';}\nB[''\\\\[list]''] = ''<ul>''; B[''\\\\[list=(\\\\w)]''] = function($0, $1) {return ''<ul style="list-style-type: ''+ (U[$1]||''disc'') +''">''}; B[''\\\\[/list]''] = ''</ul>''; B[''\\\\[\\\\*]''] = ''<li>'';\nB[''\\\\[quote(?:=([^\\\\]]+))?]''] = function($0, $1) {return ''<div class="bb-quote">''+ ($1 ? $1 +'' wrote'' : ''Quote'') +'':<blockquote>''}; B[''\\\\[/quote]''] = ''</blockquote></div>'';\nB[''\\\\[(hr|br)]''] = ''<$1 />''; B[''\\\\[sp]''] = ''&nbsp;'';\nreturn R(A(A(S, I), B));\n}\nE.preview && $(E.preview).css(''display'') != ''none'' ? E.setContent(E.oriCnt) : E.setContent(BBC2HTML(E.oriCnt = E.getContent()));\neDefPreview();', 'preview.png', 'P', 6);
REPLACE INTO `bueditor_buttons` VALUES (21, 2, 'Help', 'js: eDefHelp();', 'help.png', 'F', 10);
REPLACE INTO `bueditor_buttons` VALUES (24, 1, 'Quote', '<blockquote>%TEXT%</blockquote>', 'Quote', 'Q', -1);
REPLACE INTO `bueditor_buttons` VALUES (25, 1, 'Code', '<code>%TEXT%</code>', 'Code', 'C', 0);

-- 
-- Dumping data for table `bueditor_editors`
-- 

REPLACE INTO `bueditor_editors` VALUES (1, 'HTML', 'node/*\r\ncomment/*', 'edit-log', '%BUEDITOR/icons', '%BUEDITOR/library');
REPLACE INTO `bueditor_editors` VALUES (2, 'BBCode', 'node/*\r\ncomment/*', 'edit-log', '%BUEDITOR/icons', '%BUEDITOR/library');
