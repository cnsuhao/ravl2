// This file is part of RAVL, Recognition And Vision Library 
// file-header-ends-here
#ifndef RAVLPLOT_GUPPIHEADERS_HEADER
#define RAVLPLOT_GUPPIHEADERS_HEADER 1
//! docentry="Ravl.GUI.Data_Plotting.Guppi"
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlGuppi
//! license=unknown
//! userlevel=Develop

#include "Ravl/config.h"

#include <glib.h>
#include  "guppi-xml.h"
#include "guppi-layout-constraint.h"
#include  "guppi-defs.h"

#define __GUPPI_LAYOUT_RULE_H__ 1
BEGIN_GUPPI_DECLS

struct _GuppiLayoutRule;
typedef struct _GuppiLayoutRule GuppiLayoutRule;

typedef void (*GuppiLayoutRuleConstraintFn) (GuppiLayoutConstraint *cst, gpointer closure);

GuppiLayoutRule *guppi_layout_rule_new   (const gchar *name);
void             guppi_layout_rule_ref   (GuppiLayoutRule *rule);
void             guppi_layout_rule_unref (GuppiLayoutRule *rule);
const gchar     *guppi_layout_rule_name  (GuppiLayoutRule *rule);
void             guppi_layout_rule_lock  (GuppiLayoutRule *rule);

void                   guppi_layout_rule_add_constraint (GuppiLayoutRule *rule, GuppiLayoutConstraint *cst);
GuppiLayoutConstraint *guppi_layout_rule_new_constraint (GuppiLayoutRule *rule);

gint             guppi_layout_rule_constraint_count (GuppiLayoutRule *rule);

void             guppi_layout_rule_foreach (GuppiLayoutRule *rule,
					    GuppiLayoutRuleConstraintFn fn,
					    gpointer closure);

gboolean         guppi_layout_rule_contains (GuppiLayoutRule *rule, GuppiGeometry *geom);
gboolean         guppi_layout_rule_replace  (GuppiLayoutRule *rule, GuppiGeometry *old, GuppiGeometry *nuevo);

xmlNodePtr       guppi_layout_rule_export_xml (GuppiLayoutRule *rule, GuppiXMLDocument *doc);
GuppiLayoutRule *guppi_layout_rule_import_xml (GuppiXMLDocument *doc, xmlNodePtr node);

END_GUPPI_DECLS



#include <guppi-root-group-view.h>
#include <guppi-group-view-layout.h>

#include <guppi-root-group-state.h>
#include <guppi-root-group-view.h>
#include <guppi-root-group-item.h>
#include <guppi-group-view-layout.h>
#include <guppi-object.h>

#include <guppi-data-table-core.h>
#include <guppi-data-init.h>
#include <guppi-plot-init.h>
#include <guppi-plug-in-spec.h>
#include <guppi-useful-init.h>
#include <guppi-canvas-item.h>
#include <guppi-group-view.h>
#include <guppi-defs.h>
#include <guppi-root-group-view.h>
#include <guppi-seq-scalar-core.h>
#include <guppi-config-dialog.h>
#include <guppi-memory.h>
#include <guppi-useful.h>


#endif
