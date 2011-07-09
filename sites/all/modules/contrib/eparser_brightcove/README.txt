; $Id: README.txt,v 1.1.2.1 2009/09/01 18:32:16 andrewlevine Exp $

eparser_brightcove is an extension to the JSON parser of feedapi_eparser.
It is designed to parse a link field from a brightcove feed which can be used by
the media_brightcove and emfield/emvideo modules.

Note: this module has only been tested with the playlist read API. For example,
with this URL:
http://api.brightcove.com/services/library?command=find_playlist_by_id&playlist_id=YOUR_PLAYLIST_ID&token=YOUR_TOKEN
Please submit a patch if you can make it work with other brightcove API methods.

Instructions:
1. Install the eparser_brightcove module
2. Create a feed node with the URL pointing to your Brightcove
   API URL and the feed item node type as your video node type
   which contains an emvideo field.
3. Click the Eparser tab of your feed node and select Brightcove3
   as your feed type.
4. If you have feedapi_mapper, map the fake_bc_link field to your
   media_brightcove/emvideo field. 
