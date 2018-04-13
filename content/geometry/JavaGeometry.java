/**
 * Author: Stanford
 * License: CC0
 * Description: Java Geometry
 */
import java.util.*;
import java.awt.geom.*;
import java.io.*;
public class JavaGeometry {
    // make an Area object from the coordinates of a polygon
    static Area makeArea(double[] pts) {
        Path2D.Double p = new Path2D.Double();
        p.moveTo(pts[0], pts[1]);
        for (int i = 2; i < pts.length; i += 2) p.lineTo(pts[i], pts[i+1]);
        p.closePath();
        return new Area(p);        
    }
    // compute the area of an Area object containing several disjoint polygons
    static double computeArea(Area area) {
        double totArea = 0;
        PathIterator iter = area.getPathIterator(null);
        ArrayList<Point2D.Double> points = new ArrayList<Point2D.Double>();

        while (!iter.isDone()) {
            double[] buffer = new double[6];
            switch (iter.currentSegment(buffer)) {
            case PathIterator.SEG_MOVETO:
            case PathIterator.SEG_LINETO:
                points.add(new Point2D.Double(buffer[0], buffer[1]));
                break;
            case PathIterator.SEG_CLOSE:
                totArea += computePolygonArea(points);
                points.clear();
                break;
            }
            iter.next();
        }
        return totArea;
    }
    public static void main(String args[]) throws Exception {
        // areaB.subtract(areaA);
        // areaB.exclusiveOr (areaA);
        // areaB.add (areaA);
        // areaB.intersect (areaA);
        // (1) determine whether B - A is a single closed shape (as 
        //     opposed to multiple shapes)
        boolean isSingle = areaB.isSingular();
        // also,
        //   areaB.isEmpty();
        //   areaB.contains(x, y); // doubles
        // Finally, some useful things we didn't use in this example:
        //   Ellipse2D.Double ellipse = new Ellipse2D.Double (double x, double y, double w, double h);
        //     creates an ellipse inscribed in box with bottom-left corner (x,y)
        //     and upper-right corner (x+y,w+h)
        //   Rectangle2D.Double rect = new Rectangle2D.Double (double x, double y, double w, double h);
        //     creates a box with bottom-left corner (x,y) and upper-right corner (x+y,w+h)
        // Each of these can be embedded in an Area object (e.g., new Area (rect)).
    }
}
