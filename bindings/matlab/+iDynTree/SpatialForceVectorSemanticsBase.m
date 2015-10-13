classdef SpatialForceVectorSemanticsBase < SwigRef
  methods
    function self = SpatialForceVectorSemanticsBase(varargin)
      if nargin~=1 || ~ischar(varargin{1}) || ~strcmp(varargin{1},'_swigCreate')
        % How to get working on C side? Commented out, replaed by hack below
        %self.swigInd = iDynTreeMATLAB_wrap(322, varargin{:});
        tmp = iDynTreeMATLAB_wrap(322, varargin{:}); % FIXME
        self.swigInd = tmp.swigInd;
        tmp.swigInd = uint64(0);
      end
    end
    function delete(self)
      if self.swigInd
        iDynTreeMATLAB_wrap(323, self);
        self.swigInd=uint64(0);
      end
    end
    function varargout = check_linear2angularConsistency(self,varargin)
      [varargout{1:max(1,nargout)}] = iDynTreeMATLAB_wrap(324, self, varargin{:});
    end
    function varargout = toString(self,varargin)
      [varargout{1:max(1,nargout)}] = iDynTreeMATLAB_wrap(325, self, varargin{:});
    end
    function varargout = display(self,varargin)
      [varargout{1:max(1,nargout)}] = iDynTreeMATLAB_wrap(326, self, varargin{:});
    end
  end
  methods(Static)
  end
end