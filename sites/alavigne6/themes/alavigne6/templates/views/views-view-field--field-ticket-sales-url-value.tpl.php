<?php
$ticket_url = $row->node_data_field_date_field_ticket_sales_url_value;

if($row->node_data_field_date_field_sold_out_value == 'Yes'){
  print '<span class="soldout">' . t('Sold Out') . '</span>';
}else if($ticket_url ){
  print l(t('Get Tickets'), $ticket_url);	
}else {
  print '<span class="na-tickets">' . t('N/A') . '</span>';	
}
