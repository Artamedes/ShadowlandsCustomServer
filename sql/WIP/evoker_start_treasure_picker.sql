DELETE FROM `treasure_picker_item` WHERE (`treasure_picker`=2168 AND `bonus_id`=0 AND `index`=0) OR (`treasure_picker`=2064 AND `bonus_id`=0 AND `index`=0) OR (`treasure_picker`=2063 AND `bonus_id`=0 AND `index`=0) OR (`treasure_picker`=2071 AND `bonus_id`=0 AND `index`=0) OR (`treasure_picker`=2074 AND `bonus_id`=0 AND `index`=0) OR (`treasure_picker`=2070 AND `bonus_id`=0 AND `index`=0) OR (`treasure_picker`=2062 AND `bonus_id`=0 AND `index`=0) OR (`treasure_picker`=2319 AND `bonus_id`=0 AND `index`=0) OR (`treasure_picker`=2061 AND `bonus_id`=0 AND `index`=0) OR (`treasure_picker`=2073 AND `bonus_id`=0 AND `index`=0) OR (`treasure_picker`=2059 AND `bonus_id`=0 AND `index`=0) OR (`treasure_picker`=2072 AND `bonus_id`=0 AND `index`=0) OR (`treasure_picker`=2058 AND `bonus_id`=0 AND `index`=0) OR (`treasure_picker`=2069 AND `bonus_id`=0 AND `index`=0) OR (`treasure_picker`=2060 AND `bonus_id`=0 AND `index`=0) OR (`treasure_picker`=2068 AND `bonus_id`=0 AND `index`=0) OR (`treasure_picker`=2057 AND `bonus_id`=0 AND `index`=0);
INSERT INTO `treasure_picker_item` (`treasure_picker`, `bonus_id`, `index`, `item`, `quantity`, `modifier_list`, `modifier_value_list`, `bonus_list`) VALUES
(2168, 0, 0, 194676, 1, '28', '2150', ''),
(2064, 0, 0, 193916, 1, '28', '2150', '8774'),
(2063, 0, 0, 191809, 1, '28', '2150', '8774'),
(2071, 0, 0, 194335, 1, '28', '2150', '8774'),
(2074, 0, 0, 191808, 1, '28', '2150', '8774'),
(2070, 0, 0, 194333, 1, '28', '2150', '8774'),
(2062, 0, 0, 191811, 1, '28', '2150', '8774'),
(2319, 0, 0, 201702, 1, '28', '872', ''),
(2061, 0, 0, 191812, 1, '28', '2150', '8774'),
(2073, 0, 0, 194109, 1, '28', '2150', '8774'),
(2059, 0, 0, 191806, 1, '28', '2150', '8774'),
(2072, 0, 0, 191810, 1, '28', '2150', '8774'),
(2058, 0, 0, 191805, 1, '28', '2150', '8774'),
(2069, 0, 0, 191807, 1, '28', '2150', '8774'),
(2060, 0, 0, 193914, 1, '28', '2150', '8774'),
(2068, 0, 0, 194422, 1, '28', '2150', '8774'),
(2057, 0, 0, 193481, 1, '28', '2150', '8774');


DELETE FROM `treasure_picker_entry` WHERE `id` IN (2168, 2064, 2063, 2071, 2074, 2070, 2062, 2319, 2061, 2073, 2059, 2072, 2058, 2069, 2060, 2068, 2057);
INSERT INTO `treasure_picker_entry` (`id`, `money_reward`, `flags`) VALUES
(2168, 0, 0),
(2064, 0, 0),
(2063, 0, 0),
(2071, 0, 0),
(2074, 0, 0),
(2070, 0, 0),
(2062, 0, 0),
(2319, 0, 16),
(2061, 0, 0),
(2073, 0, 0),
(2059, 0, 0),
(2072, 0, 0),
(2058, 0, 0),
(2069, 0, 0),
(2060, 0, 0),
(2068, 0, 0),
(2057, 0, 0);