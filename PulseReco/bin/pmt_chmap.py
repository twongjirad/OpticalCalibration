

# ( FEMCH, PMT POSID )
PMT_CHMAP = { 0:1,
              1:2,
              2:3,
              3:4,   # fill-in
              4:5,
              5:6,
              6:7,   # fill-in
              7:8,
              8:9,
              9:16,  # fill-in
              10:11,
              11:12, # fill-in
              12:13, # fill-in
              32:33,
              13:14,
              14:15,
              15:10,
              16:17,
              17:18,
              18:19,
              19:20, # fill-in
              20:21, # fill-in
              21:22, # fill-in
              33:34,
              34:35,
              22:23,
              23:24,
              24:25, # fill-in
              35:36,
              25:26,
              26:28,
              27:29,
              28:30, # fill-in
              29:31,
              30:32,
              31:27 }

REVERSE_MAP = {}
for item in PMT_CHMAP.items():
    REVERSE_MAP[ item[1] ] = item[0]


def getPMTID( readoutch ):
    return PMT_CHMAP[readoutch]

def getChannel( pmtid ):
    return REVERSE_MAP[pmtid]
