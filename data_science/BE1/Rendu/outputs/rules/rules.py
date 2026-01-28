def findDecision(obj): #obj[0]: parents, obj[1]: has_nurs, obj[2]: form, obj[3]: children, obj[4]: housing, obj[5]: finance, obj[6]: social, obj[7]: health
   # {"feature": "health", "instances": 11664, "metric_value": 0.3459, "depth": 1}
   if obj[7] == 'not_recom':
      return 'not_recom'
   elif obj[7] == 'recommended':
      # {"feature": "has_nurs", "instances": 3887, "metric_value": 0.4221, "depth": 2}
      if obj[1] == 'critical':
         # {"feature": "parents", "instances": 782, "metric_value": 0.3487, "depth": 3}
         if obj[0] == 'great_pret':
            # {"feature": "housing", "instances": 263, "metric_value": 0.2915, "depth": 4}
            if obj[4] == 'critical':
               # {"feature": "form", "instances": 91, "metric_value": 0.0719, "depth": 5}
               if obj[2] == 'foster':
                  return 'spec_prior'
               elif obj[2] == 'completed':
                  return 'spec_prior'
               elif obj[2] == 'incomplete':
                  return 'spec_prior'
               elif obj[2] == 'complete':
                  return 'spec_prior'
               else:
                  return 'spec_prior'
            elif obj[4] == 'convenient':
               # {"feature": "social", "instances": 87, "metric_value": 0.3234, "depth": 5}
               if obj[6] == 'nonprob':
                  return 'priority'
               elif obj[6] == 'problematic':
                  return 'spec_prior'
               elif obj[6] == 'slightly_prob':
                  return 'priority'
               else:
                  return 'spec_prior'
            elif obj[4] == 'less_conv':
               # {"feature": "children", "instances": 85, "metric_value": 0.212, "depth": 5}
               if obj[3] == '3':
                  return 'spec_prior'
               elif obj[3] == '2':
                  return 'spec_prior'
               elif obj[3] == 'more':
                  return 'spec_prior'
               elif obj[3] == '1':
                  return 'priority'
               else:
                  return 'spec_prior'
            else:
               return 'spec_prior'
         elif obj[0] == 'pretentious':
            # {"feature": "housing", "instances": 262, "metric_value": 0.3027, "depth": 4}
            if obj[4] == 'less_conv':
               # {"feature": "children", "instances": 91, "metric_value": 0.2381, "depth": 5}
               if obj[3] == 'more':
                  return 'spec_prior'
               elif obj[3] == '2':
                  return 'spec_prior'
               elif obj[3] == '1':
                  return 'priority'
               elif obj[3] == '3':
                  return 'spec_prior'
               else:
                  return 'spec_prior'
            elif obj[4] == 'critical':
               # {"feature": "form", "instances": 87, "metric_value": 0.0752, "depth": 5}
               if obj[2] == 'completed':
                  return 'spec_prior'
               elif obj[2] == 'complete':
                  return 'spec_prior'
               elif obj[2] == 'incomplete':
                  return 'spec_prior'
               elif obj[2] == 'foster':
                  return 'spec_prior'
               else:
                  return 'spec_prior'
            elif obj[4] == 'convenient':
               # {"feature": "social", "instances": 84, "metric_value": 0.3113, "depth": 5}
               if obj[6] == 'problematic':
                  return 'spec_prior'
               elif obj[6] == 'nonprob':
                  return 'priority'
               elif obj[6] == 'slightly_prob':
                  return 'priority'
               else:
                  return 'spec_prior'
            else:
               return 'spec_prior'
         elif obj[0] == 'usual':
            # {"feature": "social", "instances": 257, "metric_value": 0.1553, "depth": 4}
            if obj[6] == 'problematic':
               # {"feature": "housing", "instances": 87, "metric_value": 0.3583, "depth": 5}
               if obj[4] == 'less_conv':
                  return 'spec_prior'
               elif obj[4] == 'convenient':
                  return 'priority'
               elif obj[4] == 'critical':
                  return 'spec_prior'
               else:
                  return 'spec_prior'
            elif obj[6] == 'nonprob':
               return 'priority'
            elif obj[6] == 'slightly_prob':
               return 'priority'
            else:
               return 'priority'
         else:
            return 'spec_prior'
      elif obj[1] == 'proper':
         # {"feature": "parents", "instances": 779, "metric_value": 0.3487, "depth": 3}
         if obj[0] == 'pretentious':
            # {"feature": "housing", "instances": 264, "metric_value": 0.2951, "depth": 4}
            if obj[4] == 'critical':
               # {"feature": "form", "instances": 91, "metric_value": 0.0726, "depth": 5}
               if obj[2] == 'incomplete':
                  return 'priority'
               elif obj[2] == 'complete':
                  return 'priority'
               elif obj[2] == 'completed':
                  return 'priority'
               elif obj[2] == 'foster':
                  return 'priority'
               else:
                  return 'priority'
            elif obj[4] == 'less_conv':
               # {"feature": "children", "instances": 90, "metric_value": 0.2357, "depth": 5}
               if obj[3] == '3':
                  return 'priority'
               elif obj[3] == '2':
                  return 'priority'
               elif obj[3] == '1':
                  return 'priority'
               elif obj[3] == 'more':
                  return 'priority'
               else:
                  return 'priority'
            elif obj[4] == 'convenient':
               # {"feature": "social", "instances": 83, "metric_value": 0.2754, "depth": 5}
               if obj[6] == 'slightly_prob':
                  return 'very_recom'
               elif obj[6] == 'nonprob':
                  return 'very_recom'
               elif obj[6] == 'problematic':
                  return 'priority'
               else:
                  return 'priority'
            else:
               return 'priority'
         elif obj[0] == 'great_pret':
            # {"feature": "social", "instances": 262, "metric_value": 0.145, "depth": 4}
            if obj[6] == 'nonprob':
               return 'priority'
            elif obj[6] == 'problematic':
               # {"feature": "children", "instances": 87, "metric_value": 0.3298, "depth": 5}
               if obj[3] == '3':
                  return 'spec_prior'
               elif obj[3] == 'more':
                  return 'spec_prior'
               elif obj[3] == '1':
                  return 'priority'
               elif obj[3] == '2':
                  return 'spec_prior'
               else:
                  return 'spec_prior'
            elif obj[6] == 'slightly_prob':
               return 'priority'
            else:
               return 'priority'
         elif obj[0] == 'usual':
            # {"feature": "social", "instances": 253, "metric_value": 0.2888, "depth": 4}
            if obj[6] == 'problematic':
               return 'priority'
            elif obj[6] == 'slightly_prob':
               # {"feature": "housing", "instances": 83, "metric_value": 0.3665, "depth": 5}
               if obj[4] == 'convenient':
                  return 'very_recom'
               elif obj[4] == 'less_conv':
                  return 'priority'
               elif obj[4] == 'critical':
                  return 'priority'
               else:
                  return 'priority'
            elif obj[6] == 'nonprob':
               # {"feature": "housing", "instances": 81, "metric_value": 0.3388, "depth": 5}
               if obj[4] == 'less_conv':
                  return 'priority'
               elif obj[4] == 'critical':
                  return 'priority'
               elif obj[4] == 'convenient':
                  return 'very_recom'
               else:
                  return 'priority'
            else:
               return 'priority'
         else:
            return 'priority'
      elif obj[1] == 'improper':
         # {"feature": "parents", "instances": 778, "metric_value": 0.3525, "depth": 3}
         if obj[0] == 'usual':
            # {"feature": "housing", "instances": 267, "metric_value": 0.2939, "depth": 4}
            if obj[4] == 'critical':
               # {"feature": "form", "instances": 92, "metric_value": 0.0704, "depth": 5}
               if obj[2] == 'foster':
                  return 'priority'
               elif obj[2] == 'incomplete':
                  return 'priority'
               elif obj[2] == 'completed':
                  return 'priority'
               elif obj[2] == 'complete':
                  return 'priority'
               else:
                  return 'priority'
            elif obj[4] == 'less_conv':
               # {"feature": "children", "instances": 90, "metric_value": 0.2323, "depth": 5}
               if obj[3] == 'more':
                  return 'priority'
               elif obj[3] == '2':
                  return 'priority'
               elif obj[3] == '3':
                  return 'priority'
               elif obj[3] == '1':
                  return 'priority'
               else:
                  return 'priority'
            elif obj[4] == 'convenient':
               # {"feature": "social", "instances": 85, "metric_value": 0.3067, "depth": 5}
               if obj[6] == 'slightly_prob':
                  return 'very_recom'
               elif obj[6] == 'nonprob':
                  return 'very_recom'
               elif obj[6] == 'problematic':
                  return 'priority'
               else:
                  return 'priority'
            else:
               return 'priority'
         elif obj[0] == 'pretentious':
            # {"feature": "social", "instances": 257, "metric_value": 0.1374, "depth": 4}
            if obj[6] == 'nonprob':
               return 'priority'
            elif obj[6] == 'slightly_prob':
               return 'priority'
            elif obj[6] == 'problematic':
               # {"feature": "housing", "instances": 81, "metric_value": 0.3275, "depth": 5}
               if obj[4] == 'critical':
                  return 'spec_prior'
               elif obj[4] == 'less_conv':
                  return 'spec_prior'
               elif obj[4] == 'convenient':
                  return 'priority'
               else:
                  return 'spec_prior'
            else:
               return 'priority'
         elif obj[0] == 'great_pret':
            # {"feature": "housing", "instances": 254, "metric_value": 0.3113, "depth": 4}
            if obj[4] == 'convenient':
               # {"feature": "social", "instances": 88, "metric_value": 0.3248, "depth": 5}
               if obj[6] == 'slightly_prob':
                  return 'priority'
               elif obj[6] == 'nonprob':
                  return 'priority'
               elif obj[6] == 'problematic':
                  return 'spec_prior'
               else:
                  return 'spec_prior'
            elif obj[4] == 'less_conv':
               # {"feature": "children", "instances": 85, "metric_value": 0.2421, "depth": 5}
               if obj[3] == '1':
                  return 'priority'
               elif obj[3] == 'more':
                  return 'spec_prior'
               elif obj[3] == '2':
                  return 'spec_prior'
               elif obj[3] == '3':
                  return 'spec_prior'
               else:
                  return 'spec_prior'
            elif obj[4] == 'critical':
               # {"feature": "form", "instances": 81, "metric_value": 0.063, "depth": 5}
               if obj[2] == 'foster':
                  return 'spec_prior'
               elif obj[2] == 'completed':
                  return 'spec_prior'
               elif obj[2] == 'complete':
                  return 'spec_prior'
               elif obj[2] == 'incomplete':
                  return 'spec_prior'
               else:
                  return 'spec_prior'
            else:
               return 'spec_prior'
         else:
            return 'priority'
      elif obj[1] == 'less_proper':
         # {"feature": "parents", "instances": 777, "metric_value": 0.3504, "depth": 3}
         if obj[0] == 'usual':
            # {"feature": "social", "instances": 266, "metric_value": 0.2981, "depth": 4}
            if obj[6] == 'slightly_prob':
               # {"feature": "housing", "instances": 91, "metric_value": 0.3259, "depth": 5}
               if obj[4] == 'convenient':
                  return 'very_recom'
               elif obj[4] == 'critical':
                  return 'priority'
               elif obj[4] == 'less_conv':
                  return 'priority'
               else:
                  return 'priority'
            elif obj[6] == 'problematic':
               return 'priority'
            elif obj[6] == 'nonprob':
               # {"feature": "housing", "instances": 86, "metric_value": 0.3399, "depth": 5}
               if obj[4] == 'less_conv':
                  return 'priority'
               elif obj[4] == 'convenient':
                  return 'very_recom'
               elif obj[4] == 'critical':
                  return 'priority'
               else:
                  return 'priority'
            else:
               return 'priority'
         elif obj[0] == 'pretentious':
            # {"feature": "social", "instances": 256, "metric_value": 0.295, "depth": 4}
            if obj[6] == 'problematic':
               return 'priority'
            elif obj[6] == 'nonprob':
               # {"feature": "housing", "instances": 85, "metric_value": 0.3369, "depth": 5}
               if obj[4] == 'convenient':
                  return 'very_recom'
               elif obj[4] == 'critical':
                  return 'priority'
               elif obj[4] == 'less_conv':
                  return 'priority'
               else:
                  return 'priority'
            elif obj[6] == 'slightly_prob':
               # {"feature": "housing", "instances": 84, "metric_value": 0.344, "depth": 5}
               if obj[4] == 'convenient':
                  return 'very_recom'
               elif obj[4] == 'less_conv':
                  return 'priority'
               elif obj[4] == 'critical':
                  return 'priority'
               else:
                  return 'priority'
            else:
               return 'priority'
         elif obj[0] == 'great_pret':
            # {"feature": "social", "instances": 255, "metric_value": 0.1525, "depth": 4}
            if obj[6] == 'problematic':
               # {"feature": "housing", "instances": 88, "metric_value": 0.3136, "depth": 5}
               if obj[4] == 'critical':
                  return 'spec_prior'
               elif obj[4] == 'less_conv':
                  return 'spec_prior'
               elif obj[4] == 'convenient':
                  return 'priority'
               else:
                  return 'spec_prior'
            elif obj[6] == 'nonprob':
               return 'priority'
            elif obj[6] == 'slightly_prob':
               return 'priority'
            else:
               return 'priority'
         else:
            return 'priority'
      elif obj[1] == 'very_crit':
         # {"feature": "housing", "instances": 771, "metric_value": 0.2991, "depth": 3}
         if obj[4] == 'less_conv':
            # {"feature": "children", "instances": 258, "metric_value": 0.2262, "depth": 4}
            if obj[3] == 'more':
               return 'spec_prior'
            elif obj[3] == '3':
               return 'spec_prior'
            elif obj[3] == '1':
               # {"feature": "social", "instances": 64, "metric_value": 0.2727, "depth": 5}
               if obj[6] == 'slightly_prob':
                  return 'priority'
               elif obj[6] == 'nonprob':
                  return 'priority'
               elif obj[6] == 'problematic':
                  return 'spec_prior'
               else:
                  return 'priority'
            elif obj[3] == '2':
               # {"feature": "form", "instances": 62, "metric_value": 0.2052, "depth": 5}
               if obj[2] == 'incomplete':
                  return 'spec_prior'
               elif obj[2] == 'foster':
                  return 'spec_prior'
               elif obj[2] == 'completed':
                  return 'priority'
               elif obj[2] == 'complete':
                  return 'priority'
               else:
                  return 'spec_prior'
            else:
               return 'spec_prior'
         elif obj[4] == 'convenient':
            # {"feature": "social", "instances": 258, "metric_value": 0.3229, "depth": 4}
            if obj[6] == 'slightly_prob':
               # {"feature": "finance", "instances": 87, "metric_value": 0.2085, "depth": 5}
               if obj[5] == 'convenient':
                  return 'priority'
               elif obj[5] == 'inconv':
                  return 'spec_prior'
               else:
                  return 'priority'
            elif obj[6] == 'problematic':
               # {"feature": "form", "instances": 86, "metric_value": 0.0603, "depth": 5}
               if obj[2] == 'complete':
                  return 'spec_prior'
               elif obj[2] == 'foster':
                  return 'spec_prior'
               elif obj[2] == 'incomplete':
                  return 'spec_prior'
               elif obj[2] == 'completed':
                  return 'spec_prior'
               else:
                  return 'spec_prior'
            elif obj[6] == 'nonprob':
               # {"feature": "finance", "instances": 85, "metric_value": 0.2326, "depth": 5}
               if obj[5] == 'inconv':
                  return 'spec_prior'
               elif obj[5] == 'convenient':
                  return 'priority'
               else:
                  return 'priority'
            else:
               return 'spec_prior'
         elif obj[4] == 'critical':
            # {"feature": "form", "instances": 255, "metric_value": 0.0705, "depth": 4}
            if obj[2] == 'foster':
               return 'spec_prior'
            elif obj[2] == 'completed':
               return 'spec_prior'
            elif obj[2] == 'incomplete':
               return 'spec_prior'
            elif obj[2] == 'complete':
               # {"feature": "children", "instances": 60, "metric_value": 0.0978, "depth": 5}
               if obj[3] == '3':
                  return 'spec_prior'
               elif obj[3] == 'more':
                  return 'spec_prior'
               elif obj[3] == '1':
                  return 'priority'
               elif obj[3] == '2':
                  return 'spec_prior'
               else:
                  return 'spec_prior'
            else:
               return 'spec_prior'
         else:
            return 'spec_prior'
      else:
         return 'priority'
   elif obj[7] == 'priority':
      # {"feature": "has_nurs", "instances": 3882, "metric_value": 0.2834, "depth": 2}
      if obj[1] == 'very_crit':
         # {"feature": "form", "instances": 781, "metric_value": 0.0197, "depth": 3}
         if obj[2] == 'complete':
            # {"feature": "children", "instances": 199, "metric_value": 0.067, "depth": 4}
            if obj[3] == '3':
               return 'spec_prior'
            elif obj[3] == 'more':
               return 'spec_prior'
            elif obj[3] == '1':
               # {"feature": "housing", "instances": 48, "metric_value": 0.1765, "depth": 5}
               if obj[4] == 'convenient':
                  return 'spec_prior'
               elif obj[4] == 'less_conv':
                  return 'spec_prior'
               elif obj[4] == 'critical':
                  return 'spec_prior'
               else:
                  return 'spec_prior'
            elif obj[3] == '2':
               return 'spec_prior'
            else:
               return 'spec_prior'
         elif obj[2] == 'completed':
            return 'spec_prior'
         elif obj[2] == 'incomplete':
            return 'spec_prior'
         elif obj[2] == 'foster':
            return 'spec_prior'
         else:
            return 'spec_prior'
      elif obj[1] == 'proper':
         # {"feature": "parents", "instances": 779, "metric_value": 0.1533, "depth": 3}
         if obj[0] == 'great_pret':
            # {"feature": "housing", "instances": 262, "metric_value": 0.3425, "depth": 4}
            if obj[4] == 'convenient':
               # {"feature": "finance", "instances": 92, "metric_value": 0.2027, "depth": 5}
               if obj[5] == 'convenient':
                  return 'priority'
               elif obj[5] == 'inconv':
                  return 'spec_prior'
               else:
                  return 'priority'
            elif obj[4] == 'critical':
               # {"feature": "form", "instances": 88, "metric_value": 0.0992, "depth": 5}
               if obj[2] == 'foster':
                  return 'spec_prior'
               elif obj[2] == 'completed':
                  return 'spec_prior'
               elif obj[2] == 'complete':
                  return 'spec_prior'
               elif obj[2] == 'incomplete':
                  return 'spec_prior'
               else:
                  return 'spec_prior'
            elif obj[4] == 'less_conv':
               # {"feature": "children", "instances": 82, "metric_value": 0.1874, "depth": 5}
               if obj[3] == '3':
                  return 'spec_prior'
               elif obj[3] == 'more':
                  return 'spec_prior'
               elif obj[3] == '1':
                  return 'priority'
               elif obj[3] == '2':
                  return 'priority'
               else:
                  return 'spec_prior'
            else:
               return 'spec_prior'
         elif obj[0] == 'usual':
            return 'priority'
         elif obj[0] == 'pretentious':
            return 'priority'
         else:
            return 'priority'
      elif obj[1] == 'less_proper':
         # {"feature": "parents", "instances": 779, "metric_value": 0.1492, "depth": 3}
         if obj[0] == 'usual':
            return 'priority'
         elif obj[0] == 'great_pret':
            # {"feature": "housing", "instances": 259, "metric_value": 0.3344, "depth": 4}
            if obj[4] == 'convenient':
               # {"feature": "finance", "instances": 88, "metric_value": 0.2082, "depth": 5}
               if obj[5] == 'convenient':
                  return 'priority'
               elif obj[5] == 'inconv':
                  return 'spec_prior'
               else:
                  return 'priority'
            elif obj[4] == 'critical':
               # {"feature": "children", "instances": 86, "metric_value": 0.0977, "depth": 5}
               if obj[3] == '2':
                  return 'spec_prior'
               elif obj[3] == 'more':
                  return 'spec_prior'
               elif obj[3] == '3':
                  return 'spec_prior'
               elif obj[3] == '1':
                  return 'spec_prior'
               else:
                  return 'spec_prior'
            elif obj[4] == 'less_conv':
               # {"feature": "children", "instances": 85, "metric_value": 0.2241, "depth": 5}
               if obj[3] == '3':
                  return 'spec_prior'
               elif obj[3] == 'more':
                  return 'spec_prior'
               elif obj[3] == '1':
                  return 'priority'
               elif obj[3] == '2':
                  return 'spec_prior'
               else:
                  return 'spec_prior'
            else:
               return 'spec_prior'
         elif obj[0] == 'pretentious':
            return 'priority'
         else:
            return 'priority'
      elif obj[1] == 'improper':
         # {"feature": "parents", "instances": 772, "metric_value": 0.1584, "depth": 3}
         if obj[0] == 'usual':
            return 'priority'
         elif obj[0] == 'pretentious':
            # {"feature": "housing", "instances": 260, "metric_value": 0.3328, "depth": 4}
            if obj[4] == 'less_conv':
               # {"feature": "children", "instances": 89, "metric_value": 0.2217, "depth": 5}
               if obj[3] == '3':
                  return 'spec_prior'
               elif obj[3] == 'more':
                  return 'spec_prior'
               elif obj[3] == '2':
                  return 'priority'
               elif obj[3] == '1':
                  return 'priority'
               else:
                  return 'spec_prior'
            elif obj[4] == 'convenient':
               # {"feature": "finance", "instances": 86, "metric_value": 0.2271, "depth": 5}
               if obj[5] == 'inconv':
                  return 'spec_prior'
               elif obj[5] == 'convenient':
                  return 'priority'
               else:
                  return 'priority'
            elif obj[4] == 'critical':
               # {"feature": "children", "instances": 85, "metric_value": 0.1027, "depth": 5}
               if obj[3] == '2':
                  return 'spec_prior'
               elif obj[3] == '1':
                  return 'spec_prior'
               elif obj[3] == 'more':
                  return 'spec_prior'
               elif obj[3] == '3':
                  return 'spec_prior'
               else:
                  return 'spec_prior'
            else:
               return 'spec_prior'
         elif obj[0] == 'great_pret':
            # {"feature": "children", "instances": 250, "metric_value": 0.0155, "depth": 4}
            if obj[3] == '3':
               return 'spec_prior'
            elif obj[3] == '2':
               return 'spec_prior'
            elif obj[3] == 'more':
               return 'spec_prior'
            elif obj[3] == '1':
               # {"feature": "form", "instances": 61, "metric_value": 0.0579, "depth": 5}
               if obj[2] == 'complete':
                  return 'spec_prior'
               elif obj[2] == 'completed':
                  return 'spec_prior'
               elif obj[2] == 'foster':
                  return 'spec_prior'
               elif obj[2] == 'incomplete':
                  return 'spec_prior'
               else:
                  return 'spec_prior'
            else:
               return 'spec_prior'
         else:
            return 'spec_prior'
      elif obj[1] == 'critical':
         # {"feature": "parents", "instances": 771, "metric_value": 0.1701, "depth": 3}
         if obj[0] == 'usual':
            # {"feature": "housing", "instances": 267, "metric_value": 0.3387, "depth": 4}
            if obj[4] == 'convenient':
               # {"feature": "finance", "instances": 90, "metric_value": 0.1956, "depth": 5}
               if obj[5] == 'inconv':
                  return 'spec_prior'
               elif obj[5] == 'convenient':
                  return 'priority'
               else:
                  return 'priority'
            elif obj[4] == 'critical':
               # {"feature": "form", "instances": 89, "metric_value": 0.0981, "depth": 5}
               if obj[2] == 'completed':
                  return 'spec_prior'
               elif obj[2] == 'incomplete':
                  return 'spec_prior'
               elif obj[2] == 'complete':
                  return 'spec_prior'
               elif obj[2] == 'foster':
                  return 'spec_prior'
               else:
                  return 'spec_prior'
            elif obj[4] == 'less_conv':
               # {"feature": "children", "instances": 88, "metric_value": 0.2248, "depth": 5}
               if obj[3] == '1':
                  return 'priority'
               elif obj[3] == '2':
                  return 'spec_prior'
               elif obj[3] == '3':
                  return 'spec_prior'
               elif obj[3] == 'more':
                  return 'spec_prior'
               else:
                  return 'spec_prior'
            else:
               return 'spec_prior'
         elif obj[0] == 'great_pret':
            # {"feature": "form", "instances": 255, "metric_value": 0.0224, "depth": 4}
            if obj[2] == 'completed':
               return 'spec_prior'
            elif obj[2] == 'foster':
               return 'spec_prior'
            elif obj[2] == 'complete':
               # {"feature": "children", "instances": 64, "metric_value": 0.0781, "depth": 5}
               if obj[3] == '1':
                  return 'spec_prior'
               elif obj[3] == '2':
                  return 'spec_prior'
               elif obj[3] == '3':
                  return 'spec_prior'
               elif obj[3] == 'more':
                  return 'spec_prior'
               else:
                  return 'spec_prior'
            elif obj[2] == 'incomplete':
               return 'spec_prior'
            else:
               return 'spec_prior'
         elif obj[0] == 'pretentious':
            # {"feature": "children", "instances": 249, "metric_value": 0.0229, "depth": 4}
            if obj[3] == 'more':
               return 'spec_prior'
            elif obj[3] == '3':
               return 'spec_prior'
            elif obj[3] == '2':
               return 'spec_prior'
            elif obj[3] == '1':
               # {"feature": "form", "instances": 58, "metric_value": 0.0841, "depth": 5}
               if obj[2] == 'complete':
                  return 'spec_prior'
               elif obj[2] == 'incomplete':
                  return 'spec_prior'
               elif obj[2] == 'completed':
                  return 'spec_prior'
               elif obj[2] == 'foster':
                  return 'spec_prior'
               else:
                  return 'spec_prior'
            else:
               return 'spec_prior'
         else:
            return 'spec_prior'
      else:
         return 'spec_prior'
   else:
      return 'not_recom'
